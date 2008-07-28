/* UDP client in the internet domain */


#include "prprf.h"
#include "prio.h"
#include "prnetdb.h"

#include <stdlib.h>
#include "contact_notary.h" 

PRBool verify_signature(char *buf, int msg_len, char *server_key);

void send_single_query(server_list *server, PRFileDesc *fd,  
					   notary_header *hdr) {
	int len, n; 
	
    PRNetAddr addr;
    PRIntervalTime timeout = PR_INTERVAL_NO_WAIT;
    addr.inet.family = PR_AF_INET;
    addr.inet.ip = server->ip_addr;
    addr.inet.port = server->port;


    len = PR_ntohs(hdr->total_len);
    n = PR_SendTo(fd, hdr, len ,0, &addr, timeout);
    PR_fprintf(PR_STDERR, "sent %d bytes to %s : %d \n", n, 
               ip_2_str(*(int*) &server->ip_addr), PR_ntohs(addr.inet.port));
   if (n < 0) 
       PR_fprintf(PR_STDERR,"Failed to send in socket\n" );
}

int recv_single_reply( PRFileDesc *fd, char *buf, int buf_len, 
            PRNetAddr *from) {

    PRIntervalTime timeout = PR_INTERVAL_NO_TIMEOUT;
    int n = PR_RecvFrom(fd,buf,buf_len,0, from, timeout);
    if (n < 0){ 
        PR_fprintf(PR_STDERR,"Failed to recvfrom in socket\n" );
    } else {
        PR_fprintf(PR_STDERR,"Recved from socket %d bytes\n", n );
   }
   return n;
}

// loop through each notary server, collecting onE 
// or more ssh_key_info* responses from each and
// storing those responses in the server's list. 
void fetch_notary_observations(SSHNotary *notary, 
		char* service_id, int timeout_secs, int max_retries) {
   PRFileDesc *fd;
   PRIntervalTime start = PR_IntervalNow(); 
   notary_header *hdr;
   int num_servers; 
   server_list *server;
   struct list_head *pos, *q;
   PRUint32 ticks_per_second = PR_TicksPerSecond(); 
   PRUint32 timeout_ticks = timeout_secs * ticks_per_second;
   PRUint32 round_len_ticks = timeout_ticks / (max_retries + 1);
   PRPollDesc pds[1];
   int retry_count = 0;
   int reply_count = 0;
   PRNetAddr recv_addr;
   char recv_buf[MAX_PACKET_LEN];
   PRBool first_reply; 

   free_key_info(notary); // free any old data we had (dw: this is observation data, right?)
   
   fd = PR_NewUDPSocket();
   if (fd == NULL) {
       PR_fprintf(PR_STDERR,"New UDP Socket Creation Error\n");
       return;
   }

   PR_fprintf(PR_STDERR,"creating request for '%s'\n", service_id);
   hdr = create_request(service_id, 9 /*ignore*/);

   // loop through each server, send each a request
   num_servers = 0;
   list_for_each_safe(pos, q, &notary->notary_servers.list){
		server = list_entry(pos, server_list, list);
                send_single_query(server, fd, hdr);
                ++num_servers;
   }

   while(reply_count < num_servers) {
     PRIntervalTime select_timeout = round_len_ticks;
     PRInt32 is_ready; 

     pds[0].fd = fd;
     pds[0].in_flags = PR_POLL_READ;
     pds[0].out_flags = 0;
     is_ready = PR_Poll(pds, 1, select_timeout);  

     if(is_ready) {
        int recv_len = recv_single_reply(fd, recv_buf, MAX_PACKET_LEN, &recv_addr);
        uint32_t server_ip = recv_addr.inet.ip;
        uint16_t server_port = recv_addr.inet.port;
        server = find_server(notary, server_ip, server_port);
        if(server == NULL) {
          DPRINTF(DEBUG_ERROR, "Could not find server state for reply message\n");  
        }else {
		DPRINTF(DEBUG_INFO, "Parsing message from: %s : %d \n", 
				ip_2_str(server->ip_addr), server->port);
		server->received_reply = 1; // got something, even if its invalid

		first_reply = server->notary_results == NULL; 
		if(!verify_signature(recv_buf, recv_len, server->public_key)) {
			DPRINTF(DEBUG_ERROR, "Droppy reply from %s:%d because of bad signature\n",
					ip_2_str(server->ip_addr), server->port); 
			server->notary_results = NULL;
		} else 
			server->notary_results = parse_message(recv_buf, recv_len);

		// count only if the server returned results.
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
		
        PRIntervalTime now = PR_IntervalNow();   
        PRIntervalTime time_diff = (PRIntervalTime)(now - start);
        if(retry_count == max_retries) {
            DPRINTF(DEBUG_INFO, "Reached max notary connect attempts \n");
            goto done;
        }

        // see if we need to retranmit
        if(time_diff > (retry_count * round_len_ticks)) {
            DPRINTF(DEBUG_SOCKET, "Retrnsmitting %d millis after start\n", time_diff);
            list_for_each_safe(pos, q, &notary->notary_servers.list){
                  server = list_entry(pos, server_list, list);
                  if(!server->received_reply) {
                    DPRINTF(DEBUG_SOCKET, "Retransmitting to %s : %d \n",
                        ip_2_str(server->ip_addr), server->port);
                    send_single_query(server, fd, hdr);
                  }
            }
            ++retry_count;
        }
    }
  }

  done:
    free(hdr);
}



