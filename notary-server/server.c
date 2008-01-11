

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "common.h"
#include "net_util.h"
#include "notary_util.h"
#include "bdb_storage.h"
#include "net_util.h"
#include "keyscan_util.h"

typedef struct {
	uint16_t port;
	uint32_t ip_addr;
	char *db_env_fname;
	char *db_fname;
} server_config;



void parse_config_file(server_config *conf, char* fname){
	char buf[1024];
	FILE *f;
	assert(fname);

	f = fopen(fname, "r");
	if(f == NULL) {
		fprintf(stderr,
		"Notary Error: Invalid conf file %s \n", fname);
		return;
	}

	while(fgets(buf, 1023,f) != NULL) {
		if(*buf == '\n') continue;
		if(*buf == '#') continue;
		int size = strlen(buf);
		buf[size - 1] = 0x0; // replace '\n' with NULL
		char *delim = strchr(buf,'=');
		if(delim == NULL) {
			DPRINTF(DEBUG_ERROR, 
				"Ignoring malformed line: %s \n", buf);
			continue;
		}
		*delim = 0x0;
	 
		char *value = delim + 1;
		DPRINTF(DEBUG_INFO, "key = '%s' value = '%s' \n", 
				buf, value);
		if(strcmp(buf,"ip_addr") == 0) { 
			conf->ip_addr = str_2_ip(value);
		} else if(strcmp(buf, "port") == 0) {
			conf->port = atoi(value);
		} else if(strcmp(buf, "db_env_fname") == 0){
			conf->db_env_fname = strdup(value);
		} else if(strcmp(buf, "db_fname") == 0) {
			conf->db_fname = strdup(value);
		} else {
			DPRINTF(DEBUG_ERROR, "Unknown config value %s : %s \n",
					buf, value);
		}
	}		
}



BOOL parse_header(notary_header *hdr, int recv_len, char** hostname_out, 
                                uint16_t *type_out){
  *hostname_out = NULL;
  if(hdr->version != 1) {
    DPRINTF(DEBUG_ERROR, "Invalid version: %d \n", hdr->version);
    return FALSE;
  }

  if(hdr->msg_type != TYPE_FETCH_REQ) {
    DPRINTF(DEBUG_ERROR, "Invalid message type: %d \n", hdr->msg_type);
    return FALSE;
  }
  int stated_total_len = ntohs(hdr->total_len);
  if(stated_total_len != recv_len) {
    DPRINTF(DEBUG_ERROR, "Stated len of packet (%d bytes) "
        "does not match  size of UDP packet read (%d bytes) \n", 
        stated_total_len, recv_len);
    return FALSE;
  }
  char *host  = (char*)(hdr+1);
  int stated_name_len = ntohs(hdr->name_len);
  int actual_name_len = strlen(host) + 1;
  if(stated_name_len != actual_name_len) {
    DPRINTF(DEBUG_ERROR, "Stated name_len (%d bytes) "
        "does not match actual len of (%d bytes) for '%s' \n", 
        stated_name_len, actual_name_len, host);
    return FALSE;
  }
  *hostname_out = host;
  *type_out = ntohs(hdr->service_type);
  return TRUE;
}

// in the future, this will build a data structure so we
// can do this ``on demand'' probes asynchronously, but for
// now we just sleep, which is a horrible hack for a single
// threaded server. shhhhhhhhhh, don't tell anyone
void request_probe(char *service) {

    int len = strlen(service) + 1; // send NULL terminator 
    DPRINTF(DEBUG_INFO,"Requesting on-demand probe for: '%s'\n", 
        service); 
    sendToUnixSock(NEW_REQUEST_SOCK_NAME, service, len);
    usleep(1500000); 
}


void sock_error(char *msg)
{
    perror(msg);
    exit(1);
}

void server_loop(DB *db, uint32_t ip_addr, uint16_t port) {

   unsigned int fromlen;
   int sock, length, n;
   struct sockaddr_in server;
   struct sockaddr_in from;
   char buf[MAX_PACKET_LEN];
   
   sock=socket(AF_INET, SOCK_DGRAM, 0);
   if (sock < 0) sock_error("Opening socket");
   length = sizeof(server);
   bzero(&server,length);
   server.sin_family=AF_INET;
   server.sin_addr.s_addr= ip_addr;
   server.sin_port=htons(port);
   if (bind(sock,(struct sockaddr *)&server,length)<0) 
       sock_error("binding");
   fromlen = sizeof(struct sockaddr_in);

   int count = 0;
   while (1) {

       n = recvfrom(sock,buf,MAX_PACKET_LEN,
           0,(struct sockaddr *)&from,&fromlen);
       if (n < 0) sock_error("recvfrom");
       

       char *host;
       uint16_t type;
       notary_header* hdr = (notary_header*)buf;
       if(! parse_header(hdr, n, &host,&type))
         continue;
       int hdr_len = HEADER_SIZE(hdr);

       DPRINTF(DEBUG_INFO,"Request for: %s (%d) len = %d from %s \n",
           host, type, n,
           ip_2_str(*(uint32_t*)&from.sin_addr.s_addr));

       BOOL first_request = TRUE; 
       int data_len = -1; 
       while(1) { 

        data_len = get_data(db,host,buf + hdr_len, 
                                         MAX_PACKET_LEN - hdr_len);
        if(data_len >= 0) break;
        if(!first_request) break; 

        first_request = FALSE; 
        request_probe(host);
        printf("Done sleeping \n"); 
       }

       int total_len = hdr_len; 
       if(data_len < 0) { 
          hdr->msg_type = TYPE_FETCH_REPLY_EMPTY; 
          hdr->sig_len = 0;
       } else { 
         // entry found 
        total_len += data_len;
        hdr->msg_type = TYPE_FETCH_REPLY_FINAL;
        hdr->sig_len = htons(SIGNATURE_LEN);
       }

       hdr->total_len = htons(total_len); 
       n = sendto(sock, buf , total_len, 
            0 ,(struct sockaddr *)&from,fromlen);
       if (n  < 0) sock_error("sendto");

       ++count;
       DPRINTF(DEBUG_INFO,"Replied with %d bytes (client # %d )\n", n, count);
   /* 
      printf("server sent: \n");
      ssh_key_info_list *list = list_from_data(buf + hdr_len, data_len,
                                                       SIGNATURE_LEN);
      print_key_info_list(list);
      free_key_info_list(list);
      */
       fflush(stderr); 
   }
 }


unsigned int notary_debug = DEBUG_ERROR  | DEBUG_DATABASE | DEBUG_INFO;

int main(int argc, char** argv) {

    server_config conf;

    if(argc != 2) {
        printf("usage: <config file> \n");
        exit(1);
    }

    parse_config_file(&conf, argv[1]);

    uint32_t env_flags = DB_CREATE | DB_INIT_MPOOL | DB_INIT_CDB;
    DB *db = bdb_open_env(conf.db_env_fname, env_flags, conf.db_fname, DB_RDONLY);
    if(db == NULL){
      printf("bdb_open failed \n");
      exit(1);
    }
    warm_db(db);
    fflush(stderr); 

    server_loop(db, conf.ip_addr, conf.port);
    
    bdb_close(db);
  
}
