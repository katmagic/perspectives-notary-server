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

// used for server load testing.  
// loads a set number of host-ids to query server for
notary_header ** load_requests(char* fname, int count){
	char buf[1024];
	FILE *f;
	assert(fname);

        int size = sizeof(notary_header*) * count;
        notary_header** all_hosts = (notary_header**)malloc(size);
        bzero(all_hosts, size);

	f = fopen(fname, "r");
	if(f == NULL) {
		fprintf(stderr,
		"couldn't open file %s \n", fname);
		exit(1);
	}

        int i;
        for(i = 0; i < count; i++) {
                fgets(buf, 1023,f);

		int size = strlen(buf);
		buf[size - 1] = 0x0; // replace '\n' with NULL
                all_hosts[i] = create_request(buf, 9 /*ignore*/);
              //  printf("all_hosts[%d] = %s \n", i, all_hosts[i]);
	}
        return all_hosts;
}



unsigned int notary_debug = DEBUG_ERROR | DEBUG_SOCKET | DEBUG_INFO;

int main(int argc, char *argv[])
{
   int sock;
   struct sockaddr_in reply_addr;

   if (argc != 4) { printf("Usage: server port num-hosts \n");
                    exit(1);
   }

   RSA *pub_key = load_public_key("../keys/public.pem");

   char fname_buf[256];
   snprintf(fname_buf, 256, "%s_hosts.txt", argv[3]);
   int count = atoi(argv[3]);

   printf("starting header loading \n");
   notary_header **all_hosts = load_requests(fname_buf, count);
   printf("done with header loading \n");
   
   sock= socket(AF_INET, SOCK_DGRAM, 0);
   if (sock < 0) {
     perror("socket");
     exit(1);
   }
   
   server_list server;
   server.ip_addr = str_2_ip(argv[1]);
   server.port = atoi(argv[2]);

   struct timeval start, end;
   gettimeofday(&start,NULL);

   int sent_total = 0, recv_total = 0;
   char recv_buf[MAX_PACKET_LEN];
   int recv_len;
   struct timeval select_timeout;
   select_timeout.tv_usec = 0;
   select_timeout.tv_sec = 0;
   fd_set readfds;
   int next_wait = 100; // prevent overrunning server buffers
   while(recv_total < count) {

        if(sent_total < count) {
            send_single_query(&server, sock, all_hosts[sent_total]);
            ++sent_total;
            printf("sent: %d \n", sent_total);
        }

        FD_ZERO(&readfds);
        FD_SET(sock, &readfds);
        int num_fds = select(sock + 1, &readfds, NULL, NULL, &select_timeout);
        if(num_fds || (next_wait == sent_total)) {
          recv_len = recv_single_reply(sock, recv_buf, MAX_PACKET_LEN, &reply_addr);
          ssh_key_info_list* list = parse_message(recv_buf, recv_len, pub_key);
          print_key_info_list(list);
          printf("\n");
          free_key_info_list(list);
          ++recv_total;
        }

        if(sent_total == next_wait) next_wait += 100;
   }
   gettimeofday(&end,NULL);
   float sec_diff = (float) (end.tv_sec - start.tv_sec);
   int usec_diff = end.tv_usec - start.tv_usec;
   float usec_fraction = ((float)(usec_diff))/(1000000.0);
   float time_result = sec_diff + usec_fraction;
   printf("Recv %d, %f seconds \n",
            recv_total, time_result);
   int i;
   for(i = 0; i < count; i++) {
    free(all_hosts[i]);
   }
   free(all_hosts);
   return 0;
}

