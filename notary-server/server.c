

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
#include "list.h" 
#include "server_common.h"

#define MAX_ONDEMAND_WAIT_SEC 3
#define ONDEMAND_CHECK_INTERVAL_SEC 1

typedef struct {
  notary_header *hdr;
  uint32_t hdr_len; 
  uint32_t req_time;
  struct sockaddr_in *addr; 
  int addr_len; 
  struct list_head list; // for linked-list
} ondemand_probe; 


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

// called to intiate an "on demand" probe.  We create a datastructure to 
// remember this specific request, and stash it on the ondemand_list.  
// We also use a UNIX socket to request that the scanner process probes
// the service_id of this request.  
void request_probe(notary_header *hdr, struct sockaddr_in *addr, int addr_len, 
                         ondemand_probe *ondemand_list) {

    int hdr_len = HEADER_SIZE(hdr);
    ondemand_probe *tmp = (ondemand_probe*)malloc(sizeof(ondemand_probe));
    tmp->hdr = (notary_header*) malloc(hdr_len);
    memcpy(tmp->hdr,hdr,hdr_len); 
    tmp->hdr_len = hdr_len; 
    struct timeval tv; 
    gettimeofday(&tv,NULL); 
    tmp->req_time = tv.tv_sec;
    tmp->addr = (struct sockaddr_in*) malloc(addr_len); 
    memcpy(tmp->addr,addr,addr_len); 
    tmp->addr_len = addr_len; 
     
    __list_add(&tmp->list, &(ondemand_list->list), 
                  (ondemand_list->list.next)); 

    // we need to actually tell the scanning process to 
    // probe this service_id 
    char *service_id = (char*)(tmp->hdr + 1);
    request_ondemand_probe(service_id); 
}


void sock_error(char *msg)
{
    perror(msg);
    exit(1);
}

int attempt_lookup_and_reply(DB *db, int sock, notary_header *hdr, 
        struct sockaddr_in *remote_addr, unsigned int addr_len, 
        BOOL send_on_miss) { 
  char buf[MAX_PACKET_LEN];

  int hdr_len = HEADER_SIZE(hdr);
  char *service_id = (char*)(hdr + 1); 

  int data_len = get_data(db,service_id, buf + hdr_len, 
      MAX_PACKET_LEN - hdr_len);
  if(data_len < 0 && !send_on_miss)
    return 0; 

  int total_len = hdr_len; 
  if(data_len > 0) { 
    total_len += data_len;
    hdr->msg_type = TYPE_FETCH_REPLY_FINAL;
    hdr->sig_len = htons(SIGNATURE_LEN);
  } else {
    hdr->msg_type = TYPE_FETCH_REPLY_EMPTY; 
    hdr->sig_len = 0;
  } 
  hdr->total_len = htons(total_len); 
  memcpy(buf,hdr,hdr_len); 
  int n = sendto(sock, buf , total_len, 
      0 ,(struct sockaddr *)remote_addr,addr_len);
  if (n  < 0) 
    sock_error("sendto");

    /*  ------ Disabled for Production ---------
  else     
     DPRINTF(DEBUG_INFO,"Replied with %d bytes about %s\n",n,service_id); 
     DPRINTF(DEBUG_INFO,"Sent to %s : \n",
	ip_2_str(*(uint32_t*)&remote_addr->sin_addr.s_addr)); 
     ssh_key_info_list *list = list_from_data(buf + hdr_len, data_len,
     SIGNATURE_LEN);
     print_key_info_list(list);
     free_key_info_list(list);
     */
  fflush(stderr); 
  return n; 
} 


void check_ondemand_list(DB *db, ondemand_probe *ondemand_list, 
                                 int sock, uint32_t cur_time) { 

    ondemand_probe *entry; 
    struct list_head *pos, *q; 
    list_for_each_safe(pos,q,&(ondemand_list->list)) { 
      entry = list_entry(pos, ondemand_probe, list);
      char *service_id = (char*)(entry->hdr + 1); 
      DPRINTF(DEBUG_INFO, "OD-entry: %s \n", service_id);
    
      BOOL send_on_miss = (entry->req_time + MAX_ONDEMAND_WAIT_SEC
                             < cur_time); 
      int bytes = attempt_lookup_and_reply(db,sock,entry->hdr, 
                          entry->addr, entry->addr_len, send_on_miss); 

      if(bytes > 0 || send_on_miss) { 
        // transmitted packet.  remove it from list and free it
        DPRINTF(DEBUG_INFO,"Sent %d bytes for ondemand probe for %s \n",
                        bytes, service_id); 
        list_del(&entry->list); 
        free(entry->hdr);
        free(entry->addr);
        free(entry); 
      } 
    } 

} 


int main_sock; 
void on_kill(int signal) { 
	close(main_sock); 
} 


void server_loop(DB *db, uint32_t ip_addr, uint16_t port){

   unsigned int fromlen;
   int main_sock, length, n;
   struct sockaddr_in server;
   struct sockaddr_in from;
   char buf[MAX_PACKET_LEN];
   uint32_t last_ondemand_check = 0; // never

   ondemand_probe ondemand_list; 
   INIT_LIST_HEAD(&ondemand_list.list); 

   main_sock=socket(AF_INET, SOCK_DGRAM, 0);
   if (main_sock < 0) sock_error("Opening socket");
   length = sizeof(server);
   bzero(&server,length);
   server.sin_family=AF_INET;
   server.sin_addr.s_addr= ip_addr;
   server.sin_port=htons(port);
   if (bind(main_sock,(struct sockaddr *)&server,length)<0) 
       sock_error("binding");
   fromlen = sizeof(struct sockaddr_in);

   fd_set readset; 
   struct timeval timeout,now;
   while (1) {
      timeout.tv_sec = 1; 
      timeout.tv_usec = 0; 

      FD_ZERO(&readset); 
      FD_SET(main_sock, &readset);
      int result = select(main_sock+1,&readset,NULL,NULL,&timeout); 
      if(result < 0) { 
        perror("select"); 
      } else if(result > 0) {
        // socket is ready 
        assert(FD_ISSET(main_sock,&readset)); 
        n = recvfrom(main_sock,buf,MAX_PACKET_LEN,
           0,(struct sockaddr *)&from,&fromlen);
        if (n < 0) sock_error("recvfrom");
       
        char *host;
        uint16_t type;
        notary_header* hdr = (notary_header*)buf;
        if(! parse_header(hdr, n, &host,&type))
          continue;

        DPRINTF(DEBUG_INFO,"Request for: %s (%d) len = %d \n",host, type, n); 
	/* 
		--- Disabled for Production --- 
        DPRINTF(DEBUG_INFO,"Request from: %s \n", 
		ip_2_str(*(uint32_t*)&from.sin_addr.s_addr));
	*/  

        int bytes = attempt_lookup_and_reply(db,main_sock,hdr,&from,fromlen,FALSE); 
  
        // if database did not contain an entry for service-id, request probe 
        if(bytes == 0) 
         request_probe(hdr,&from,fromlen,&ondemand_list);
      }

      gettimeofday(&now,NULL); 
      if(last_ondemand_check + ONDEMAND_CHECK_INTERVAL_SEC < (uint32_t)now.tv_sec){
        last_ondemand_check = now.tv_sec;
        check_ondemand_list(db, &ondemand_list, main_sock, now.tv_sec);  
      } 
   } // end while 
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
