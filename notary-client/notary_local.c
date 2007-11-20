#include <sys/types.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "../common/common.h"
#include "../common/notary_util.h"
#include "../common/net_util.h"
#include "notary_local.h"

unsigned int notary_debug = DEBUG_NONE;

void add_notary_server(SSHNotary *notary, uint32_t ip_address, uint16_t port){
	server_list *tmp = (server_list*)malloc(sizeof(server_list));
	tmp->ip_addr = ip_address;
	INIT_LIST_HEAD(&(tmp->notary_results.list));
	tmp->port = port;
	tmp->contact_succeeded = 0;
	__list_add(&tmp->list,&(notary->notary_servers.list),
                            (notary->notary_servers.list.next));
	DPRINTF(DEBUG_INFO, "Adding notary server: %s : %d \n",
			inet_ntoa(*(struct in_addr*)&ip_address), tmp->port);
}

SSHNotary* init_ssh_notary(){

	SSHNotary *n = (SSHNotary*)malloc(sizeof(SSHNotary));
	INIT_LIST_HEAD(&n->notary_servers.list);
	return n;
}

// for each server, loop through its probe_info list
// and free all content.
// this function should be called when the notary is free,
// or when a new call to 'contact_probe_servers' is made
void free_key_info(SSHNotary* notary) {

	server_list *server;
	struct list_head *pos;
	list_for_each(pos,&notary->notary_servers.list){
		server = list_entry(pos, server_list, list);
			
                free_key_info_list(&server->notary_results); 
        }
}
 
void free_ssh_notary(SSHNotary* notary){
	free_key_info(notary); // call before freeing server info

	server_list *server;
	struct list_head *pos, *q;
	list_for_each_safe(pos, q, &notary->notary_servers.list){
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
void probe_for_key(SSHNotary *notary, int time_out_msecs /*ignored*/,
		char* name, uint16_t key_type, 
		uint16_t service_port) {

	free_key_info(notary); // free any old data we had

        // TODO: removed call to notaries

}

// print all information received from probe servers
void print_probe_info(SSHNotary *notary) {
	server_list *server;
	struct list_head *outer_pos;
	list_for_each(outer_pos,&notary->notary_servers.list){
		server = list_entry(outer_pos, server_list, list);

		printf("***********  Probes from server %s ********** \n", 
			inet_ntoa(*(struct in_addr*)&server->ip_addr));
		
		print_key_info_list(&(server->notary_results));
	}
}

#define MAX_NUM_KEYS 64

/*  
 *
 *  this function needs to be rewritten now that we do not use full
 *  ssh keys on the client (instead we use 16-byte hashes)

// a new print function that collects all information about a particular
// key together.  It should be much more readable.  
void print_probe_info2(SSHNotary *notary) {
	Key* all_keys[MAX_NUM_KEYS];
	int key_count = 0;

	// loop through each reply list to find all unique keys
	server_list *server;
	struct list_head *outer_pos, *inner_pos;
	list_for_each(outer_pos,&notary->notary_servers.list){
		server = list_entry(outer_pos, server_list, list);
		ssh_key_info_list *list_elem;
		list_for_each(inner_pos,&(server->notary_results.list)) {
			list_elem = list_entry(inner_pos, 	
				ssh_key_info_list, list);

			BOOL key_found = FALSE;
			int i;
                        Key *k = info_to_ssh_key(list_elem->info);
                        // test if we've already seen this key
			for(i = 0; i < key_count; i++) {
       				if(key_equal(all_keys[i], k)){
					key_found = TRUE;
                                        break;
                                }
			}
			if(!key_found && key_count < MAX_NUM_KEYS) {
                                // if not, add it to the list
				all_keys[key_count] = k;
				key_count++;
			}else {
                            free(k);
                        }
		}
	}

	// loop through each key, printing all observations for that key
	int j;
	for(j = 0; j < key_count; j++) {
       	
		printf("\n***************** [ Key #%d of %d ] ********************* \n\n",
				(j+1), key_count);	
       		key_write(all_keys[j], stdout);
        	fputs("\n\n", stdout);

		server_list *server;
		struct list_head *outer_pos, *inner_pos;
		list_for_each(outer_pos,&notary->notary_servers.list){
			server = list_entry(outer_pos, server_list, list);

			printf("Observed Key-timespans from Notary Server = %s :\n", 
                            ip_2_str(server->ip_addr));
                        ssh_key_info_list *list_elem;
                        list_for_each(inner_pos, &server->notary_results.list) {
                          list_elem = list_entry(inner_pos, ssh_key_info_list, list);
                          Key *k = info_to_ssh_key(list_elem->info);
                          if(key_equal(all_keys[j], k)) {
                            print_key_info_timespans(list_elem->info);
                          }
                        }
                }
        }


}
*/

// loads a file where probe servers are listed one per line:
// <server ip> <server port> 
// (no per-probe server public keys yet) 
void load_notary_servers(SSHNotary *notary, char* fname){
	char buf[1024];
	FILE *f;
	assert(fname);

	f = fopen(fname, "r");
	if(f == NULL) {
		fprintf(stderr,
		"Notary Error: Invalid probe-server file %s \n", fname);
		return;
	}

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
	 
		uint32_t ip_addr;
		inet_aton(buf, (struct in_addr *)&ip_addr);
		int port = (uint16_t) atoi(delim + 1);
		add_notary_server(notary, ip_addr, port);
	
	}
}
