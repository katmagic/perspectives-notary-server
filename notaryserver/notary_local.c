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

unsigned int notary_debug = DEBUG_ALL;

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

// for each server, loop through its probe_info list
// and free all content.
// this function should be called when the notary is free,
// or when a new call to 'contact_probe_servers' is made
void free_key_info(SSHNotary* notary) {

	server_list *server;
	struct list_head *outer_pos, *inner_pos;
	list_for_each(outer_pos,&notary->probe_servers.list){
		server = list_entry(outer_pos, server_list, list);
			
		ssh_msg_list *list_elem;
		list_for_each(inner_pos,&(server->current_info.list)) {
			list_elem = list_entry(inner_pos, 	
				ssh_msg_list, list);
			ssh_key_info* key_info = 
			   (ssh_key_info*)HDR2DATA(list_elem->hdr);
	
		}

	}
}
 
void free_ssh_notary(SSHNotary* notary){
	server_list *server;
	struct list_head *pos, *q;
	list_for_each_safe(pos, q, &notary->probe_servers.list){
		server = list_entry(pos, server_list, list);
		list_del(&server->list);
		free(server);
	}
	free(notary);
}

	// loop through each probe server, collecting one
	// or more ssh_key_info* responses from each and
	// storing those responses in the server's list. 
// TODO: implement timeout functionality
void contact_probe_servers(SSHNotary *notary, int time_out_msecs /*ignored*/,
		char* name, uint16_t key_type, 
		uint16_t service_port) {

	server_list *server;
	struct list_head *pos;
	DPRINTF(DEBUG_INFO, "entering get-key loop\n");
	list_for_each(pos,&notary->probe_servers.list){
		server = list_entry(pos, server_list, list);
		DPRINTF(DEBUG_INFO, "list head = %x next = %x prev = %x\n", 
				pos, pos->next, pos->prev);
		INIT_LIST_HEAD(&(server->current_info.list));
		get_key_info_ssh(&server->current_info, server->ip_addr, 
			server->port,name, service_port, key_type);
	}
}

// print all information received from probe servers
void print_probe_info(SSHNotary *notary) {

	server_list *server;
	struct list_head *outer_pos, *inner_pos;
	list_for_each(outer_pos,&notary->probe_servers.list){
		server = list_entry(outer_pos, server_list, list);

		DPRINTF(DEBUG_INFO, "Probes from server %s \n", 
			inet_ntoa(*(struct in_addr*)&server->ip_addr));
			
		ssh_msg_list *list_elem;
		list_for_each(inner_pos,&(server->current_info.list)) {
			list_elem = list_entry(inner_pos, 	
				ssh_msg_list, list);
			ssh_key_info* key_info = (ssh_key_info*)
				HDR2DATA(list_elem->hdr);
			int blob_size = ntohs(key_info->key_len_bytes);
			char* blob_start = (char*)(key_info + 1);
        	
			DPRINTF(DEBUG_MESSAGE, "blob_size = %d \n", blob_size);
			Key* key = key_from_blob(blob_start, blob_size);

			IF_DEBUG(DEBUG_MESSAGE) {
       				printf("Got key: \n");
       				key_write(key, stdout);
        			fputs("\n", stdout);
				printf("IP address = %s \n", 
				inet_ntoa(*(struct in_addr*)&key_info->ip_addr));
			}
			int num_probes = ntohs(key_info->num_probes);
		
			DPRINTF(DEBUG_MESSAGE,"extracting %d probe timestamps \n", 
				num_probes);
			int* probes_start = (int*) (blob_start + blob_size);
			int i;
			for(i = 0; i < num_probes; i++) {
				DPRINTF(DEBUG_MESSAGE, "probe[%d] = %d \n", 
					i, ntohl(probes_start[i]));
			}
		}
	
	}
}

// loads a file where probe servers are listed one per line:
// <server ip> <server port> 
// (no per-probe server public keys yet) 
void load_probe_servers(SSHNotary *notary, char* fname){
	char *buf = NULL;
	size_t n = 0;
	FILE *f;
	int size = 0; 
	assert(fname);

	f = fopen(fname, "r");
	while((size = getline(&buf, &n, f)) >= 0) {
		if(size <= 1) continue;
		if(*buf == '#') continue;
		buf[size - 1] = 0x0; // replace '\n' with NULL
		char *delim = strchr(buf,' ');
		if(delim == NULL) {
			DPRINTF(DEBUG_ERROR, 
				"Ignoring malformed line: %s \n", buf);
			continue;
		}
		*delim = 0x0;
		
		server_list *tmp = (server_list*)malloc(sizeof(server_list));
		tmp->port = (uint16_t) atoi(delim + 1);
		inet_aton(buf, (struct in_addr *)&(tmp->ip_addr));
		list_add(&(tmp->list), &(notary->probe_servers.list));
		DPRINTF(DEBUG_INFO, "Probe server: %s : %d \n",
			buf, tmp->port);
	}
}
