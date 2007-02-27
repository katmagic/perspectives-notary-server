
#include <sys/types.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "../common.h"


int main(int argc, char** argv) {

	char buf[MAX_PACKET_LEN];
	struct sockaddr_in myaddr, remote;
	int sock;
	notary_header* hdr = (notary_header*)buf;
	char *name = "nity.stanford.edu";
	char *server_ip_str = "128.2.213.64";

	bzero(&myaddr, sizeof(struct sockaddr_in));
	myaddr.sin_family = AF_INET;
	remote.sin_family = AF_INET;
	remote.sin_port = htons(NOTARY_SERVER_PORT);
	if(!inet_aton(server_ip_str, &(remote.sin_addr))) {
		fprintf(stderr, "cannot parse ip: %s \n", server_ip_str);
		exit(-1);
	}

	if ((sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_IP)) == -1) {
   		perror("could not create server socket\n");
    		exit(-1);
  	}

	if(bind(sock, (struct sockaddr*) &myaddr, sizeof(myaddr))
		== -1) {
               	perror("could not bind to emphemeral local port");
                exit(-1);
	}

        socklen_t fromlen = sizeof(struct sockaddr_in);


	bzero(hdr, sizeof(notary_header));
	hdr->version = 1;
	hdr->msg_type = TYPE_FETCH_REQ;
	int name_len = strlen(name) + 1;
	hdr->name_len = htons(name_len);
	int total_message_len = sizeof(notary_header) + name_len;
	char* data_start = (char*) (hdr + 1);
	memcpy(data_start, name, name_len);
	printf("sending name: %s \n", data_start);

	socklen_t remotelen = sizeof(struct sockaddr_in);
       	int n = sendto(sock, hdr , total_message_len,
                  0,(struct sockaddr *) &remote, remotelen);
       	if (n  < 0) perror("sendto");

	printf("done\n");

	
       	int msg_size = recvfrom(sock, buf, MAX_PACKET_LEN, 0,
		(struct sockaddr *)&remote, &remotelen);
       	if (msg_size < 0)
		perror("recvfrom returned negative\n");

	if(hdr->msg_type == TYPE_FETCH_REPLY_FINAL) {
		printf("received fetch reply! \n");
	}else {
		printf("received unknown type: %d \n", hdr->msg_type);
	}

}
