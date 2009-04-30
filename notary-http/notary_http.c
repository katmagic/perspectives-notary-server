#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <arpa/inet.h>
#include "net_util.h"
#include "notary_util.h"
#include "notary_local.h"
#include "parse.h"
#include "bdb_storage.h"
#include "server_common.h"
#include "str_buffer.h" 
#include "pthread.h"

#define LISTENQ 1024
#define XML_RESP_LEN_DEFAULT 1024

// these values mean that during an on-demand probe
// the client may see a server-side latency of up to
// ONDEMAND_SLEEP_SEC * (ONDEMAND_MAX_TRIES - 1) seconds
#define ONDEMAND_SLEEP_SEC 1
#define ONDEMAND_MAX_TRIES 4

//TODO in fatal_error close db?
//TODO look for memory leaks try valgrind

int read_request(int sockfd, char *buf, int buflen);
void http_server_loop(uint32_t ip_addr, uint16_t port);
void process(int sockfd);
void fatal_error(char *msg);
void* thread_start(void *connfd);
int send404(int sock);
char* db_get_xml(char *service_id);



unsigned int notary_debug = 
//DEBUG_ERROR | DEBUG_SOCKET | DEBUG_INFO | DEBUG_CRYPTO;
DEBUG_ERROR | DEBUG_INFO; 

int main_sock; 
DB *db;

int main(int argc, char **argv){
    uint32_t env_flags;
    server_config conf;

    if(argc != 2){ 
        puts("usage: <config file>");
        return 0;
    }

    parse_config_file(&conf, argv[1]);

    env_flags = DB_CREATE | DB_INIT_MPOOL | DB_INIT_CDB | DB_THREAD;
    db = bdb_open_env(conf.db_env_fname, env_flags, conf.db_fname, DB_RDONLY);
    if(db == NULL) fatal_error("bdb_open failed");
    warm_db(db);

    http_server_loop(conf.ip_addr, conf.port);
    bdb_close(db);
}

void on_kill(int signal) { 
	close(main_sock); 
} 

void http_server_loop(uint32_t ip_addr, uint16_t port){
    int on = 1;
    long connfd;
    struct sockaddr_in server, client;
    socklen_t clientlen;
    pthread_t tid;

    /* Prepare the socket */
    main_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (main_sock < 0) fatal_error("Opening socket");

    memset(&server, 0, sizeof(server));
    server.sin_family      = AF_INET;
    server.sin_addr.s_addr = ip_addr;
    server.sin_port        = htons(port);

    if(setsockopt(main_sock, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on))) { 
        fatal_error("socket option"); 
    } 

    if (bind(main_sock, (struct sockaddr *)&server, sizeof(server)) < 0){
        fatal_error("binding");
    }

    if (listen(main_sock, LISTENQ) < 0) fatal_error("listen"); 

    while (1){
        clientlen = sizeof(client);
        connfd = accept(main_sock, (struct sockaddr *) &client, &clientlen);
        if (connfd < 0) 
		continue;

        pthread_create(&tid, NULL, thread_start, (void *)connfd);
        pthread_detach(tid);
    }
}

void* thread_start(void *connfd){
    process((long)connfd);
    if (close((long)connfd) < 0){ 
       	DPRINTF(DEBUG_ERROR,"Failed Socket Close\n");
    }
    return NULL;
}

void process(int sockfd){
    int len, xml_buf_len;
    char req_buf[2048];
    char req_buf_copy[2048]; 
    char service_id[1024]; // FIXME: use #define
    char *state, *xml_buf = NULL;
    char *param, *value, *host, *port, *styp;

    if ((len = read_request(sockfd, req_buf, sizeof(req_buf))) < 0){
        return;
    }
    // for debugging, store a copy of the pre-parsed request
    strncpy(req_buf_copy,req_buf,sizeof(req_buf_copy));
    // based on code above, req_buf will fit, but just in case
    req_buf_copy[sizeof(req_buf_copy) - 1] = 0; 

    if (parse_begin(&state, req_buf) < 0){
    	DPRINTF(DEBUG_INFO,"No args, sending 404: '%s'\n",req_buf_copy); 
        send404(sockfd); 
        return; 
    }

    host = NULL;
    port = NULL;
    styp = NULL;
    while(parse_next(&state, &param, &value) >= 0){
        if (strcmp(param, "host") == 0){
            host = value;
        }
        else if (strcmp(param, "port") == 0){
            port = value;
        }
        else if(strcmp(param, "service_type") == 0){
            styp = value;
        }
    }

    if (!(host && port && styp)){
    	DPRINTF(DEBUG_INFO,"Bad args, sending 404: '%s'\n",req_buf_copy); 
        send404(sockfd);
        return;
    }
    snprintf(service_id, sizeof(service_id), "%s:%s,%s", host, port, styp);
    DPRINTF(DEBUG_INFO,"Request for '%s'\n",service_id); 

    // when a db lookup returns no results, this loop waits
    // for the result of an on-demand probe
    int num_tries = 0; 
    while(!xml_buf) { 
    	xml_buf = db_get_xml(service_id);
	if(xml_buf) 
	  break; 
	
	++num_tries;
	if(num_tries == 1) { 
 	  request_ondemand_probe(service_id);
	}
 
    	if (num_tries >= ONDEMAND_MAX_TRIES){
    	   DPRINTF(DEBUG_INFO,"Timeout of on-demand probe for '%s'\n",
							service_id); 
           send404(sockfd);
           goto done;
    	}
	sleep(1); 
    } 
    xml_buf_len = strlen(xml_buf); 
    DPRINTF(DEBUG_INFO,"Reply for '%s' of %zu bytes:\n",
			service_id, strlen(xml_buf)); 
    //DPRINTF(DEBUG_INFO,"'%s'\n", xml_buf); 

    len = snprintf(req_buf, sizeof(req_buf), 
            "HTTP/1.0 200 OK\r\n"
            "Server: Perspectves Http Server\r\n"
            "Content-length: %d\r\n"
            "Content-type: text/xml\r\n\r\n", xml_buf_len);

    if (send(sockfd, req_buf, len, 0) < 0) 
	goto done; 

    if (send(sockfd, xml_buf, xml_buf_len, 0) < 0) 
    goto done;

done:
    free(xml_buf); 	
}

int send404(int sockfd){
    char * req_buf = 
        "HTTP/1.0 404 Not Found\r\n"
        "Server: Perspectves Http Server\r\n"
        "Connection: close\r\n"
        "Content-Type: text/html\r\n"
        "Content-Length: 0\r\n\r\n";

    if (send(sockfd, req_buf, strlen(req_buf), 0) < 0){
        return -1;
    }
    return 0;
}

char* db_get_xml(char *service_id){
    int db_data_len;
    struct list_head *pos, *tmp;
    char tmp_buf[MAX_PACKET_LEN];
    char db_data[MAX_PACKET_LEN]; // valid? 
    ssh_key_info_list *info_list, *cur;

    db_data_len = get_data(db, service_id, db_data, sizeof(db_data),
						DB_DBT_MALLOC);
    if (db_data_len < 0){
        return NULL; 
    }

    str_buffer *b = str_buffer_new(XML_RESP_LEN_DEFAULT);   
    char *sig_ptr = db_data + db_data_len - SIGNATURE_LEN;
    char * sig64 = base64((unsigned char*)sig_ptr, SIGNATURE_LEN); 
    snprintf(tmp_buf, sizeof(tmp_buf), 
	"<notary_reply version=\"1\" sig_type=\"rsa-md5\" "
	"sig=\"%s\">\n",sig64);
    str_buffer_append(b,tmp_buf); 

    info_list = list_from_data(db_data, db_data_len, SIGNATURE_LEN);
    list_for_each_safe(pos, tmp, &info_list->list){
        cur = list_entry(pos, ssh_key_info_list, list);
        char *key_info_xml = xml_from_key_info(cur->info);
        str_buffer_append(b,key_info_xml);
        free(key_info_xml);  
    }
    str_buffer_append(b,"</notary_reply>\n"); 
    char *str = str_buffer_get(b); 
    str_buffer_free(b); 
    free_key_info_list(info_list); 
    free(sig64);
    return str;  
}

// Reads from a socket until a  full line of an 
// HTTP request (i.e., until the '\r\n' line terminator is seen).  
// On success, 'buf' contains the line with '\r\n' removed as a
// null-terminated string.  On error, return -1 and the contents 
// of 'buf' is undefined.  
int read_request(int sockfd, char *buf, int buflen){
    char *search_start = buf;
    int bytes_read = 0;

    fd_set readfds; 
    struct timeval timeout; 
    while (buflen > 0){
        FD_ZERO(&readfds);
	FD_SET(sockfd,&readfds);
	timeout.tv_sec = 5; 
	timeout.tv_usec = 0;  
	int ret = select(sockfd + 1, &readfds, NULL, NULL, &timeout);  
	if(ret == 0) { 
    		DPRINTF(DEBUG_ERROR, "client timeout\n"); 
		return -1; 
	}  
	int recv_len = read(sockfd, buf + bytes_read, buflen - bytes_read);
	
        if (recv_len < 0) { 
		perror("Error reading client socket"); 
		return -1; 
	} 
        if (recv_len == 0) { 
		DPRINTF(DEBUG_ERROR, "Truncated client request, "
		"no newline found\n"); 
		return  -1; 
	}

	bytes_read += recv_len; 
	// temporarily null terminate for \r\n check 
        buf[bytes_read] = 0;
        char *found = strstr(search_start, "\r\n");

        if (found != NULL){
            *found = 0; //strip \r\n
            return (found - buf);
        }
	// '\r' and '\n' could be in different reads
	search_start += bytes_read - 1;
    }
    DPRINTF(DEBUG_ERROR, "Ran out of buffer before we received a newline\n"); 
    return -1; /* Never got \r\n */
}

void fatal_error(char *msg){
    perror(msg);
    exit(1);
}
