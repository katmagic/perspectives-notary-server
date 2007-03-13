
#include <sys/types.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "notary_local.h"

int main(int argc, char** argv) {

	if(argc < 4) {
		fprintf(stderr, "usage: notary_client <probe-server file>"
				" <host> <port> <key-type>");
		exit(1);
	}

	uint16_t key_type = SSH_KEYTYPE_RSA;
	if(argc == 5) {
		if(strcmp(argv[4],"dsa") == 0)
			key_type = SSH_KEYTYPE_DSA;
		else if(strcmp(argv[4],"rsa1") == 0)
			key_type = SSH_KEYTYPE_RSA1;
	}	

	// initialize library with server info
	SSHNotary *notary = init_ssh_notary();
	
	load_probe_servers(notary, argv[1]);

	// set key acceptance policy

	check_ssh_key(notary, argv[2], key_type, atoi(argv[3]), NULL); 

}
