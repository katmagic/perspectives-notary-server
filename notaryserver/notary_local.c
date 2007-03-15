#include <sys/types.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "../common.h"
#include "contact_probe_server.h"
#include "notary_local.h"

void add_probe_server(SSHNotary *notary, uint32_t ip_address, uint16_t port){
	server_list *tmp = (server_list*)malloc(sizeof(server_list));
	tmp->ip_addr = ip_address;
	tmp->port = port;
	list_add(&tmp->list,&(notary->probe_servers.list));
}

SSHNotary* init_ssh_notary(){
	// TODO: give access to local key cache? 
	SSHNotary *n = (SSHNotary*)malloc(sizeof(SSHNotary));
	INIT_LIST_HEAD(&n->probe_servers.list);
	return n;
}
 
void free_ssh_notary(SSHNotary* notary){
	server_list *server;
	struct list_head *pos, *q;
	list_for_each_safe(pos, q, &notary->probe_servers.list){
		server = list_entry(pos, server_list, list);
		list_del(&server->list);
		free(server);
	}
}


void check_ssh_key(SSHNotary *notary, char* name, uint16_t key_type, 
		uint16_t service_port,Key *key) {

//	struct sockaddr_in from;
//	char buf[MAX_PACKET_LEN];
	
	server_list *server;
	struct list_head *pos;
	list_for_each(pos,&notary->probe_servers.list){
		server = list_entry(pos, server_list, list);
		ssh_key_info *tmp = get_key_info_ssh(server->ip_addr, 
			server->port,name, service_port, key_type);

		int blob_size = ntohs(tmp->key_len_bytes);
		char* blob_start = (char*)(tmp + 1);
        	printf("blob_size = %d \n", blob_size);
		Key* key = key_from_blob(blob_start, blob_size);

       		printf("Got key: \n");
       		key_write(key, stdout);
        	fputs("\n", stdout);
		printf("IP address = %s \n", 
		inet_ntoa(*(struct in_addr*)&tmp->ip_addr));
	}

	// free list
}

// loads a file where probe servers are listed one per line:
// <server ip> <server port> 
// (no per-probe server public keys yet) 
void load_probe_servers(SSHNotary *notary, char* fname){
	char *buf;
	size_t n = 0;
	FILE *f;
	int size; 
	assert(fname);

	f = fopen(fname, "r");
	while((size = getline(&buf, &n, f)) >= 0) {
		if(size <= 1) continue;
		if(*buf == '#') continue;
		buf[size - 1] = 0x0; // replace '\n' with NULL
		char *delim = strchr(buf,' ');
		if(delim == NULL) {
			fprintf(stderr,"Ignoring malformed line: %s \n", buf);
			continue;
		}
		*delim = 0x0;
		
		server_list *tmp = (server_list*)malloc(sizeof(server_list));
		tmp->port = (uint16_t) atoi(delim + 1);
		inet_aton(buf, (struct in_addr *)&(tmp->ip_addr));
		list_add(&(tmp->list), &(notary->probe_servers.list));
	}
}
