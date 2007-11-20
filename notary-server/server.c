
#include "common.h"
#include "net_util.h"
#include "notary_util.h"
#include "bdb_storage.h"
#include "net_util.h"

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


void sock_error(char *msg)
{
    perror(msg);
    exit(1);
}

void server_loop(DB *db, uint16_t port) {

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
   server.sin_addr.s_addr= INADDR_ANY; //str_2_ip("128.2.134.90");
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

       unsigned int data_len = get_data(db,host,buf + hdr_len, 
                                         MAX_PACKET_LEN - hdr_len);
       if(data_len < 0) 
         continue;
      
       int total_len = data_len + hdr_len;
       hdr->msg_type = TYPE_FETCH_REPLY_FINAL;
       hdr->total_len = htons(total_len);
       hdr->sig_len = htons(SIGNATURE_LEN);

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
   }
 }


unsigned int notary_debug = DEBUG_ERROR | DEBUG_DATABASE;

int main(int argc, char** argv) {

    if(argc != 3) {
        printf("usage: <db-filename> <listen-port> \n");
        exit(1);
    }

    uint32_t env_flags = DB_CREATE | DB_INIT_MPOOL | DB_INIT_CDB;
    DB *db = bdb_open_env("/notary", env_flags, argv[1], DB_RDONLY);
    if(db == NULL){
      printf("bdb_open failed \n");
      exit(1);
    }
    warm_db(db);

    server_loop(db, atoi(argv[2]));
    
    bdb_close(db);
  
}
