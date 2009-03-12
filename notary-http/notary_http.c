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
#define LISTENQ 1024

/* TODO server_config and parse_config_file should be moved to common so the
 * code isn't replicated. Email dan about this */
//TODO in fatal_error close db?
//TODO look for memory leaks try valgrind

int read_request(int sockfd, char *buf, int buflen);
void http_server_loop(DB *db, uint32_t ip_addr, uint16_t port);
void process(DB *db, int sockfd);
void fatal_error(char *msg);
int db_get_xml(DB *db, char *buf, int bufsize, char *host, char *port, 
        char *service_type);

unsigned int notary_debug = 
DEBUG_ERROR | DEBUG_SOCKET | DEBUG_INFO | DEBUG_CRYPTO;

int main(int argc, char **argv){
    DB *db;
    uint32_t env_flags;
    server_config conf;

    if(argc != 2){ 
        puts("usage: <config file>");
        return 0;
    }

    parse_config_file(&conf, argv[1]);

    env_flags = DB_CREATE | DB_INIT_MPOOL | DB_INIT_CDB;
    db = bdb_open_env(conf.db_env_fname, env_flags, conf.db_fname, DB_RDONLY);
    if(db == NULL) fatal_error("bdb_open failed");
    warm_db(db);

    http_server_loop(db, conf.ip_addr, conf.port);
    bdb_close(db);
}

void http_server_loop(DB *db, uint32_t ip_addr, uint16_t port){
    int sock, connfd, status;
    struct sockaddr_in server, client;
    socklen_t clientlen;

    /* Prepare the socket */
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) fatal_error("Opening socket");

    memset(&server, 0, sizeof(server));
    server.sin_family      = AF_INET;
    server.sin_addr.s_addr = ip_addr;
    server.sin_port        = htons(port);

    if (bind(sock, (struct sockaddr *)&server, sizeof(server)) < 0){
        fatal_error("binding");
    }

    if (listen(sock, LISTENQ) < 0) fatal_error("listen"); 

    clientlen = sizeof(client);
    while (1){
        connfd = accept(sock, (struct sockaddr *) &client, &clientlen);
        if (connfd < 0) fatal_error("accept"); 

        if (fork() == 0){
            process(db, connfd);
            if (close(connfd) < 0){ 
                fatal_error("Failed Socket Close");
            }
            bdb_close(db);
            close(connfd);
            exit(0);
        }
        close(connfd);

        //Reap children
        while(waitpid(-1, &status, WNOHANG) > 0);
    }
}

void process(DB *db, int sockfd){
    int len, xml_buf_len;
    char xml_buf[MAX_PACKET_LEN];
    char req_buf[2048];
    char *state;
    char *param, *value, *host, *port, *styp;

    if ((len = read_request(sockfd, req_buf, sizeof(req_buf))) <= 0){
        return;
    }

    if (parse_begin(&state, req_buf) < 0) return; 

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

    if (!host || !port || !styp){
        return;
    }

    xml_buf_len = db_get_xml(db, xml_buf, sizeof(xml_buf), host, port, styp);
    if (xml_buf_len < 0) return; 

    len = snprintf(req_buf, sizeof(req_buf), 
            "HTTP/1.0 200 OK\r\n"
            "Server: Perspectves Http Server\r\n"
            "Content-length: %d\r\n"
            "Content-type: text/xml\r\n\r\n", xml_buf_len);

    if (send(sockfd, req_buf, len, 0) < 0)         return; 
    if (send(sockfd, xml_buf, xml_buf_len, 0) < 0) return;
}

int db_get_xml(DB *db, char *buf, int buf_size, char *host, char *port, 
        char *service_type){
    int db_data_len, tmp_len, ret_len;
    struct list_head *pos, *tmp;
    char tmp_buf[MAX_PACKET_LEN];
    char db_data[MAX_PACKET_LEN];
    ssh_key_info_list *info_list, *cur;
   
    ret_len = 0;
    snprintf(tmp_buf, sizeof(tmp_buf), 
            "%s:%s,%s", host, port, service_type);
    db_data_len = get_data(db, tmp_buf, db_data, sizeof(db_data));
    if (db_data_len < 0){
        puts("db lookup failed");
        return -1; 
    }

    tmp_len = snprintf(buf, buf_size, 
            "<server>\n");
    ret_len += tmp_len;
    buf     += tmp_len;
    buf_size -= tmp_len;

    info_list = list_from_data(db_data, db_data_len, SIGNATURE_LEN);
    list_for_each_safe(pos, tmp, &info_list->list){
        cur = list_entry(pos, ssh_key_info_list, list);
        xml_from_key_info(tmp_buf, sizeof(tmp_buf), cur->info);
    }
    ret_len += snprintf(buf, buf_size, "%s</server>\n",tmp_buf);
    return ret_len;
}

/*O(n^2)!*/
int read_request(int sockfd, char *buf, int buflen){
    char *found, *place;
    int recv_len, request_len;

    place = buf;
    buflen--;/*Hack so I can always null terminate safely*/
    request_len = 0;
    while (buflen > 0){
        recv_len = recv(sockfd, place, buflen, 0);

        if (recv_len  < 0) return -1; 
        if (recv_len == 0) return  0; 

        place[recv_len] = 0;
        /* Check for \r\n\r\n */
        found = strstr(buf, "\r\n\r\n");

        if (found != NULL){
            found += 4; //account for \r\n\r\n
            *(found + 1) = 0;
            return (found - buf);
        }
        place  += recv_len;
        buflen -= recv_len;
    }
    return -1; /* Never got \r\n\r\n */
}

void fatal_error(char *msg){
    perror(msg);
    exit(1);
}
