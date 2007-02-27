#include <sys/types.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sqlite3.h>

#include "config.h"
#include "../common.h"
#include "contact_probe_server.h"

void catch_sig(int sig_num) {
        printf("ouch, got signal %d ! Exiting \n", sig_num);
        fflush(stdout);
        exit(1);
}

void send_reply(config_data *config, 
	struct sockaddr_in *from, notary_header *hdr){

	socklen_t remotelen = sizeof(struct sockaddr_in);
	int total_message_len = sizeof(notary_header); // no data for now

	hdr->msg_type = TYPE_FETCH_REPLY_FINAL;

       	int n = sendto(config->server_sock, hdr , total_message_len,
                  0,(struct sockaddr *) from, remotelen);
       	if (n  < 0) perror("sendto");

	printf("sent reply (size = %d) to %s:%d\n",
         	  n , inet_ntoa(from->sin_addr), 
			ntohs(from->sin_port));
}


void initialize(int argc, char** argv, config_data *config) {

	// set-up server socket
	struct sockaddr_in myaddr;
	if ((config->server_sock = 
		socket(AF_INET, SOCK_DGRAM, IPPROTO_IP)) == -1) {
   		perror("could not create server socket\n");
    		exit(-1);
  	}
  	bzero(&myaddr, sizeof(myaddr));
  	myaddr.sin_family = AF_INET;
  	myaddr.sin_port = htons(NOTARY_SERVER_PORT);

  	if(bind(config->server_sock, (struct sockaddr *) 
		&myaddr, sizeof(myaddr)) == -1) {
    		perror("server could not bind to port");
    		exit(-1);
  	}

	// set-up sockets to probe servers
	SSL* conn = getSSLConnection("128.2.213.64", 2221);
	config->probe_servers.push_back(conn);
}

int main(int argc, char **argv) {

	config_data config;
	struct sockaddr_in from;
	char buf[MAX_PACKET_LEN];
	initialize(argc, argv, &config);

	socklen_t fromlen = sizeof(struct sockaddr_in);
   	while (1) {
		printf("waiting for incoming message \n");
       		int msg_size = recvfrom(config.server_sock, 
			buf, MAX_PACKET_LEN, 0,
			(struct sockaddr *)&from, &fromlen);
       		if (msg_size < 0) {
			perror("recvfrom returned negative\n");
			continue;
		}

	  	printf("Incoming message (size = %d) from %s:%d\n",
         	  msg_size, inet_ntoa(from.sin_addr), ntohs(from.sin_port));

		notary_header* hdr = (notary_header*) buf;
		if(hdr->version != 1) {
			printf("ignoring packet with invalid version!\n");
			continue;
		}		
	
		if(hdr->msg_type == TYPE_FETCH_REQ){
			printf("received fetch request \n");
			char* data_start = (char*) (hdr + 1);
			printf("received request for: %s \n",
				data_start);
			printf("header name size = %d \n",
				ntohs(hdr->name_len));

			// create response based on type
			contact_probe_server(hdr, msg_size,
				config.probe_servers[0]);

			send_reply(&config, &from, hdr);

		}else {
			printf("received unknown type: %d \n",
				hdr->msg_type);
		}
	}

	return 0; // never reached
}
