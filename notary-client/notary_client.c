/* UDP client in the internet domain */
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "notary_util.h"
#include "common.h"
#include "net_util.h"
#include "notary_crypto.h"
#include "notary_client.h"

// caller should free memory
notary_header* create_request(char*hostname, uint16_t service_type) {
        int name_len = strlen(hostname) + 1;
        int total_len = sizeof(notary_header) + name_len;
        notary_header* hdr = (notary_header*)malloc(total_len);
        hdr->version = 1;
        hdr->msg_type = TYPE_FETCH_REQ;
        hdr->total_len = htons(total_len);
        hdr->name_len = htons(name_len);
        hdr->service_type = htons(service_type);
	char* name_start = (char*)(hdr+1);
	memcpy(name_start, hostname, name_len);
        return hdr;
}

void send_single_query(struct sockaddr_in *server, int sock,  
                           notary_header *hdr) {
   int length=sizeof(struct sockaddr_in);
   int len = ntohs(hdr->total_len);
 //  printf("sending %d bytes to server \n", len);
   int n=sendto(sock,hdr, len ,0,
        (struct sockaddr*)server,length);
   if (n < 0) 
     perror("Sendto");
}

int recv_single_reply( int sock, char *buf, int buf_len) {

   struct sockaddr_in from;
   uint32_t length=sizeof(struct sockaddr_in);
   int n = recvfrom(sock,buf,buf_len,0,
        (struct sockaddr*)&from, &length);
   if (n < 0){ 
     perror("recvfrom");
   } else {
     DPRINTF(DEBUG_SOCKET, "Received %d bytes from %s \n", n, 
       ip_2_str(*(uint32_t*)&from.sin_addr.s_addr));
   }
   return n;
}

ssh_key_info_list* parse_message(char *buf, int msg_len, RSA* pub_key) {
   notary_header *hdr = (notary_header*)buf;
   int hdr_len = HEADER_SIZE(hdr);
   char *serviceid = (char*) (hdr + 1);
   DPRINTF(DEBUG_INFO, "Reply for serviceid = '%s' \n", serviceid);
   char *data = ((char*)buf) + hdr_len;
   int total_len = ntohs(hdr->total_len);
   if(total_len != msg_len) {
      DPRINTF(DEBUG_ERROR, "Length mismatch header = %d actual = %d \n",
                              total_len, msg_len);
      return NULL;
   }
   int data_len = total_len - hdr_len;
   if(!verify_message_signature(hdr, pub_key)) {
      DPRINTF(DEBUG_ERROR, "**** Signature is invalid **** \n");
      return NULL;
   }

   return list_from_data(data, data_len, SIGNATURE_LEN);
}


