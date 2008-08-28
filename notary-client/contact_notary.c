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
#include "contact_notary.h"
#include "notary_local.h"

void send_single_query(server_list *server, int sock,  
                           notary_header *hdr) {

   struct sockaddr_in server_addr;
   server_addr.sin_addr = *(struct in_addr*)&(server->ip_addr);
   server_addr.sin_port = htons(server->port);
   server_addr.sin_family = AF_INET;
   int length=sizeof(struct sockaddr_in);
   int len = ntohs(hdr->total_len);
   int n=sendto(sock,hdr, len ,0,
        (struct sockaddr*)&server_addr,length);
   DPRINTF(DEBUG_SOCKET, "sent %d bytes to %s : %d \n", n, 
                ip_2_str(*(int*) &server_addr.sin_addr), ntohs(server_addr.sin_port));
   if (n < 0) 
     perror("Sendto");
}

int recv_single_reply( int sock, char *buf, int buf_len, 
            struct sockaddr_in *from) {

   uint32_t length=sizeof(struct sockaddr_in);
   int n = recvfrom(sock,buf,buf_len,0,
        (struct sockaddr*)from, &length);
   if (n < 0){ 
     perror("recvfrom");
   } else {
     DPRINTF(DEBUG_SOCKET, "Received %d bytes from %s \n", n, 
       ip_2_str(*(uint32_t*)&(from->sin_addr.s_addr)));
   }
   return n;
}

// loop through each notary server, collecting onE 
// or more ssh_key_info* responses from each and
// storing those responses in the server's list. 
void fetch_notary_observations(SSHNotary *notary, 
		char* service_id, int timeout_secs, int max_retries) {

   BOOL first_reply; 
   free_key_info(notary); // free any old data we had
   DPRINTF(DEBUG_SOCKET, "Querying for '%s' with timeout of %d secs\n",
		service_id, timeout_secs);    
   int sock = socket(AF_INET, SOCK_DGRAM, 0);
   if (sock < 0) {
     perror("socket");
     return;
   }
   
   struct timeval start, now, select_timeout;
   gettimeofday(&start, NULL);

   notary_header* hdr = create_request(service_id, 9 /*ignore*/);

   // loop through each server, send each a request
   int num_servers = 0;
   server_list *server;
   struct list_head *pos, *q;
   list_for_each_safe(pos, q, &notary->notary_servers.list){
		server = list_entry(pos, server_list, list);
                send_single_query(server, sock, hdr);
                ++num_servers;
   }


   fd_set readfds;
   int retry_count = 0;
   float round_len_millis = (((float)timeout_secs * 1000) / (max_retries + 1));
   int reply_count = 0;
   float s_timeout_millis = round_len_millis;
   struct sockaddr_in recv_addr;
   char recv_buf[MAX_PACKET_LEN];
   
   while(reply_count < num_servers) {
     //printf("reply_count = %d num_server = %d \n", reply_count, num_servers);

     FD_ZERO(&readfds);
     FD_SET(sock, &readfds);
     select_timeout.tv_sec = MILLIS_TO_TIMEVAL_SEC(s_timeout_millis);  
     select_timeout.tv_usec = MILLIS_TO_TIMEVAL_USEC(s_timeout_millis); 
     int is_ready = select(sock + 1, &readfds, NULL, NULL, &select_timeout);
     if(is_ready) {
        int recv_len = recv_single_reply(sock, recv_buf, MAX_PACKET_LEN, &recv_addr);
        uint32_t server_ip = *(uint32_t*)&(recv_addr.sin_addr.s_addr);
        uint16_t server_port = ntohs(recv_addr.sin_port);
        server = find_server(notary, server_ip, server_port);
        if(server == NULL) {
          DPRINTF(DEBUG_ERROR, "Could not find server state for reply message\n");  
        }else {
         // TODO: change parse_message API to verify that reply is
         // for the same service-id for which we queried
          DPRINTF(DEBUG_INFO, "Parsing message from: %s : %d \n", 
              ip_2_str(server->ip_addr), server->port);
          server->received_reply = 1; // got something, even if its invalid
	  first_reply = server->notary_results == NULL;
		
	  printf("************ this was changed to be compatible with FF code **\n"); 
	  exit(1); 
 
          //server->notary_results = parse_message(recv_buf, recv_len, server->public_key);
          // count only if the server returned new results.
	  // This isn't great, but it stops us from quitting early during
	  // on demand probes, which is a big problem.  Eventually, the server
	  // should be sure to never return an empty result if an on-demand 
	  // probe is in progress. 
	  if(server->notary_results && first_reply) {  
		DPRINTF(DEBUG_SOCKET,"new valid reply received ****** \n"); 
		++reply_count;
	  } 
        }
    }else {
        if(retry_count == max_retries) {
            DPRINTF(DEBUG_INFO, "Reached max notary connect attempts \n");
            goto done;
        }

        gettimeofday(&now,NULL);
        float time_diff = TIMEVAL_DIFF_MILLIS(now,start);

        // see if we need to retranmit
        if(time_diff > (retry_count * round_len_millis)) {
            DPRINTF(DEBUG_SOCKET, "Retransmitting %.0f millis after start\n", time_diff);
            list_for_each_safe(pos, q, &notary->notary_servers.list){
                  server = list_entry(pos, server_list, list);
                  if(!server->received_reply) {
                    DPRINTF(DEBUG_SOCKET, "Retransmitting to %s : %d \n",
                        ip_2_str(server->ip_addr), server->port);
                    send_single_query(server, sock, hdr);
                  }
            }
            ++retry_count;
        }
    }
  }

  done:
    free(hdr);
}



