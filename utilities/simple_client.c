/* UDP client in the internet domain */
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "notary_local.h"
#include "contact_notary.h"
#include "notary_util.h"
#include "common.h"
#include "net_util.h"
#include "notary_crypto.h"

unsigned int notary_debug = DEBUG_ERROR | DEBUG_SOCKET | DEBUG_INFO | DEBUG_CRYPTO;

int main(int argc, char *argv[])
{

   if (argc != 4) { printf("Usage: <server> <port> <service-id>  \n");
                    exit(1);
   }

   RSA *pub_key = load_public_key("../keys/public.pem");
   
   int sock;

   sock= socket(AF_INET, SOCK_DGRAM, 0);
   if (sock < 0) {
     perror("socket");
     exit(1);
   }

   //hack
   server_list server;
   server.ip_addr = str_2_ip(argv[1]);
   server.port = atoi(argv[2]);

   notary_header* hdr = create_request(argv[3], 9 /*ignore*/);

   send_single_query(&server, sock, hdr);
   free(hdr);
   printf("Sent request for service-id = '%s' \n", argv[3]);

   fd_set readfds;
   FD_ZERO(&readfds);
   FD_SET(sock, &readfds);
   struct timeval select_timeout;
   select_timeout.tv_sec = 6;
   select_timeout.tv_usec = 0;

   int is_ready = select(sock + 1, &readfds, NULL, NULL, &select_timeout);
   if(!is_ready) {
        printf("Failed to contact server.  Try again later \n");
        exit(1);
   }
   char recv_buf[MAX_PACKET_LEN];
   struct sockaddr_in reply_addr;
   int recv_len = recv_single_reply(sock, recv_buf, MAX_PACKET_LEN, &reply_addr);
	
   //FIXME:  Disabling signature check b/c of API change
   ssh_key_info_list* list = parse_message(recv_buf, recv_len);
   if(list == NULL) {
      printf("Failed to parse message and create list of keys \n");
      exit(1);
   }
   print_key_info_list(stdout, list);
   printf("\n");
   free_key_info_list(list);

   return 0;
}

