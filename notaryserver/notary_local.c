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

unsigned int notary_debug = DEBUG_NONE;

void add_probe_server(SSHNotary *notary, uint32_t ip_address, uint16_t port){
	server_list *tmp = (server_list*)malloc(sizeof(server_list));
	tmp->ip_addr = ip_address;
	INIT_LIST_HEAD(&(tmp->probe_results.list));
	tmp->port = port;
	list_add(&tmp->list,&(notary->probe_servers.list));
}

SSHNotary* init_ssh_notary(char* cert_file){
	// TODO: give access to local key cache? 
	SSHNotary *n = (SSHNotary*)malloc(sizeof(SSHNotary));
	INIT_LIST_HEAD(&n->probe_servers.list);
	n->cert_file = cert_file;
	return n;
}

// for each server, loop through its probe_info list
// and free all content.
// this function should be called when the notary is free,
// or when a new call to 'contact_probe_servers' is made
void free_key_info(SSHNotary* notary) {

	server_list *server;
	struct list_head *outer_pos, *inner_pos, *q;
	list_for_each(outer_pos,&notary->probe_servers.list){
		server = list_entry(outer_pos, server_list, list);
			
		ssh_result_list *list_elem;
		list_for_each_safe(inner_pos,q, &(server->probe_results.list)) {
			list_elem = list_entry(inner_pos, 	
				ssh_result_list, list);
			key_free(list_elem->key);
			free(list_elem->probes);
			list_del(&(list_elem->list));
			free(list_elem);
		}

	}
}
 
void free_ssh_notary(SSHNotary* notary){
	free_key_info(notary); // call before freeing server info

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

	free_key_info(notary); // free any old data we had

	server_list *server;
	struct list_head *pos;
	DPRINTF(DEBUG_INFO, "entering get-key loop\n");
	list_for_each(pos,&notary->probe_servers.list){
		server = list_entry(pos, server_list, list);
		get_key_info_ssh(&server->probe_results, server->ip_addr, 
			server->port,name, service_port, key_type,
			notary->cert_file);
	}
}

void set_consistent_length(server_list *server, Key* host_key) {

	ssh_result_list *match = NULL;
	ssh_result_list *list_elem;
	struct list_head *inner_pos;
	list_for_each(inner_pos,&(server->probe_results.list)) {
		list_elem = list_entry(inner_pos, 	
			ssh_result_list, list);
		Key* probe_key = list_elem->key;

       		if(!key_equal(probe_key,host_key))
			continue;
				
		if(match != NULL) {
			DPRINTF(DEBUG_ERROR, 
			"Error, more than one message received"
			" for a single dns-name, key pair \n");
			continue; // ok, for now
		}
		match = list_elem;
	}
		
	if(match == NULL) {
		server->consistent_length = 0;
		return; 
	}
	int oldest_no_conflict = server->probe_results.probes[0];
		 
	list_for_each(inner_pos,&(server->probe_results.list)) {
		list_elem = list_entry(inner_pos, 	
			ssh_result_list, list);
		if(list_elem == match) continue;
		
		int index = list_elem->num_probes - 1;
		int most_recent = list_elem->probes[index];
				
		// test if a conflicting key has been seen
		// by this server since it first saw the good
		// key.  If so, find if there's a observation
		// of the same key more recently
		if(most_recent >= oldest_no_conflict) { 
			int i;
			// goes from oldest to newest
			oldest_no_conflict = 0;
			for(i = 0; i < match->num_probes; i++) {
				if(match->probes[i] < most_recent){
					oldest_no_conflict = match->probes[i];
					break;
				}
			}
		}
	}
	
	server->consistent_length = oldest_no_conflict;	

}

// TODO: send IP address too?  

int check_key_consistency(SSHNotary *notary, Key* host_key) {

	server_list *server;

	struct list_head *outer_pos;
	list_for_each(outer_pos,&notary->probe_servers.list){
		server = list_entry(outer_pos, server_list, list);
		set_consistent_length(server, host_key);
	}
	int min_consistent_len = -1;
	list_for_each(outer_pos,&notary->probe_servers.list){
		server = list_entry(outer_pos, server_list, list);
		if(min_consistent_len == -1){
			min_consistent_len = server->consistent_length;
		} else {
			min_consistent_len = min(min_consistent_len,
						server->consistent_length);
		}
	}
	return min_consistent_len;
}

// print all information received from probe servers
void print_probe_info(SSHNotary *notary) {

	server_list *server;
	struct list_head *outer_pos, *inner_pos;
	list_for_each(outer_pos,&notary->probe_servers.list){
		server = list_entry(outer_pos, server_list, list);

		printf("***********  Probes from server %s ********** \n", 
			inet_ntoa(*(struct in_addr*)&server->ip_addr));
			
		ssh_result_list *list_elem;
		list_for_each(inner_pos,&(server->probe_results.list)) {
			list_elem = list_entry(inner_pos, 	
				ssh_result_list, list);
	
       			printf("Got key: \n");
       			key_write(list_elem->key, stdout);
        		fputs("\n", stdout);
			printf("IP address = %s \n", 
			inet_ntoa(*(struct in_addr*)&list_elem->ip_addr));
		
			int i;
			for(i = 0; i < list_elem->num_probes; i++) {
				printf("probe[%d] = %d \n", i, 
					list_elem->probes[i]);
			}
		}
	
	}
}

// loads a file where probe servers are listed one per line:
// <server ip> <server port> 
// (no per-probe server public keys yet) 
void load_probe_servers(SSHNotary *notary, char* fname){
	char buf[1024];
	size_t n = 0;
	FILE *f;
	assert(fname);

	f = fopen(fname, "r");
	while(fgets(buf, 1023,f) != NULL) {
		if(*buf == '\n') continue;
		if(*buf == '#') continue;
		int size = strlen(buf);
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
		INIT_LIST_HEAD(&(tmp->probe_results.list));
		inet_aton(buf, (struct in_addr *)&(tmp->ip_addr));
		list_add(&(tmp->list), &(notary->probe_servers.list));
		DPRINTF(DEBUG_INFO, "Probe server: %s : %d \n",
			buf, tmp->port);
	}
}
