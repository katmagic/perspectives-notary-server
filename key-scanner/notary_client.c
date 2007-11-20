
#include <sys/types.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "notary_local.h"
#include "key.h"

#define SELF_SIGNED_CERT "../keys/probe_server.cert"

int main(int argc, char** argv) {

	if(argc < 4) {
		fprintf(stderr, "usage: notary_client <probe-server file>"
				" <host> <port> <key-type>\n");
		exit(1);
	}

	uint16_t key_type = KEY_RSA;
	if(argc == 5) {
		if(strcmp(argv[4],"dsa") == 0)
			key_type = KEY_DSA;
		else if(strcmp(argv[4],"rsa1") == 0)
			key_type = KEY_RSA1;
	}	

	// initialize library with server info
	SSHNotary *notary = init_ssh_notary(SELF_SIGNED_CERT);

	load_probe_servers(notary, argv[1]);

	// set key acceptance policy

	contact_probe_servers(notary, 5000,argv[2], 
		key_type, atoi(argv[3])); 

	print_probe_info(notary);

	//check_key_consistency(notary, NULL);

	free_ssh_notary(notary);

}
