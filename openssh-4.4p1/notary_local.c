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
	INIT_LIST_HEAD(&(tmp->probe_results.list));
	tmp->port = port;
	tmp->contact_succeeded = 0;
	list_add(&tmp->list,&(notary->probe_servers.list));
	DPRINTF(DEBUG_INFO, "Adding Probe server: %s : %d \n",
			inet_ntoa(*(struct in_addr*)&ip_address), tmp->port);
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
			free(list_elem->timestamps);
			free(list_elem->addresses);
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
void probe_for_key(SSHNotary *notary, int time_out_msecs /*ignored*/,
		char* name, uint16_t key_type, 
		uint16_t service_port) {

	free_key_info(notary); // free any old data we had

	FILE* f = fopen(notary->cert_file, "r");
	if(f == NULL) {
		fprintf(stderr,
			"Notary Error: Invalid certificate file %s \n", 
			notary->cert_file);
		return;
	}

	contact_probe_servers(&notary->probe_servers, name, 
			key_type,service_port, notary->cert_file);
	
}
/*
void set_consistent_length(server_list *server, Key* host_key) {

	server->contains_inconsistency = FALSE; // default

	// match is set to the ssh_result_list struct
	// that has the same key (type and value) as the
	// key passed into the function
	ssh_result_list *match = NULL;
	ssh_result_list *result;
	struct list_head *inner_pos;
	list_for_each(inner_pos,&(server->probe_results.list)) {
		result = list_entry(inner_pos, 	
			ssh_result_list, list);
		Key* probe_key = result->key;

		if(probe_key->type != host_key->type) 
			continue; // ignore keys of different types

       		if(!key_equal(probe_key,host_key)) {
			// type is same, but key is different.  Inconsistent!
			server->contains_inconsistency = TRUE;
		}
				
		if(match != NULL) {
			DPRINTF(DEBUG_ERROR, 
			"Error, more than one message received"
			" for a single dns-name, key pair \n");
			continue; // ok, for now
		}
		match = result;
	}
		
	if(match == NULL) {
		server->consistent_length = 0;
		return; 
	}
	int oldest_no_conflict = match->timestamps[0];
 
	list_for_each(inner_pos,&(server->probe_results.list)) {
		result = list_entry(inner_pos, 	
			ssh_result_list, list);
		if(result == match) continue;
		
		int index = result->num_probes - 1;
		int most_recent = result->timestamps[index];
				
		// test if a conflicting key has been seen
		// by this server since it first saw the good
		// key.  If so, find if there's a observation
		// of the same key more recently
		if(most_recent >= oldest_no_conflict) { 
			int i;
			// goes from oldest to newest
			oldest_no_conflict = 0;
			for(i = 0; i < match->num_probes; i++) {
				if(match->timestamps[i] < most_recent){
					oldest_no_conflict = match->timestamps[i];
					break;
				}
			}
		}
	}
	
	server->consistent_length = oldest_no_conflict;	

}
*/

// find the most recent key seen by any server that has the 
// same type as the host key, but different content
int getMostRecentConflict(SSHNotary *notary, Key* host_key) {
	int most_recent_conflict = -1;

	struct list_head *outer_pos, *inner_pos;
	server_list *server;
	list_for_each(outer_pos,&notary->probe_servers.list){
		server = list_entry(outer_pos, server_list, list);
		ssh_result_list *result;
		list_for_each(inner_pos,&(server->probe_results.list)) {
			result = list_entry(inner_pos, ssh_result_list, list);
			Key* probe_key = result->key;

			if(probe_key->type != host_key->type) 
				continue; // ignore keys of different types
			if(key_equal(probe_key, host_key))
				continue; // ignore keys that match host_key

			int last_saw_key = 
				result->timestamps[result->num_probes - 1];
			
			if(most_recent_conflict < last_saw_key){
				most_recent_conflict = last_saw_key;
			}
				
		}

	}
	return most_recent_conflict;
}

// returns the first timestamp of when any probe server 
// saw a key that matches 'host_key'
int getOldestCorrectSighting(SSHNotary *notary, Key* host_key) {
	int oldest_correct = -1;

	struct list_head *outer_pos, *inner_pos;
	server_list *server;
	list_for_each(outer_pos,&notary->probe_servers.list){
		server = list_entry(outer_pos, server_list, list);
		ssh_result_list *result;
		list_for_each(inner_pos,&(server->probe_results.list)) {
			result = list_entry(inner_pos, ssh_result_list, list);
			Key* probe_key = result->key;

			if(key_equal(probe_key, host_key)){

				int first_saw_key = result->timestamps[0];
				if(oldest_correct == -1 ||
					oldest_correct > first_saw_key){
					oldest_correct = first_saw_key;
				}
				
			}
		}

	}
	return oldest_correct;
}

// for each server, it finds the 'freshest' probe timestamp
// from that server, and then tells you the least fresh of
// each of these timestamps
int getMostStaleProbe(SSHNotary *notary) {
	int most_stale = -1;

	struct list_head *outer_pos, *inner_pos;
	server_list *server;
	list_for_each(outer_pos,&notary->probe_servers.list){
		server = list_entry(outer_pos, server_list, list);
		ssh_result_list *result;
			
		int last_probe = -1;
		list_for_each(inner_pos,&(server->probe_results.list)) {
			result = list_entry(inner_pos, ssh_result_list, list);
				
			int last_probe_for_key = 
				result->timestamps[result->num_probes - 1];
			if(last_probe_for_key > last_probe ||
				last_probe == -1) 
				last_probe = last_probe_for_key;
		}
		if(most_stale == -1){ 
			most_stale = last_probe;
		} else if(last_probe != -1 && last_probe < most_stale){
			most_stale = last_probe;
		}

	}
	return most_stale;
}

/*
// TODO: send IP address too?  
void check_key_consistency(SSHNotary *notary, Key* host_key, int* consistency_len,
		BOOL* sawInconsistency) {

	server_list *server;
	*sawInconsistency = FALSE; // by default, no inconsistencies

	int min_consistent_len = -1;
	struct list_head *outer_pos;
	list_for_each(outer_pos,&notary->probe_servers.list){
		server = list_entry(outer_pos, server_list, list);
		set_consistent_length(server, host_key);

		if(min_consistent_len == -1){
			min_consistent_len = server->consistent_length;
		} else {
			min_consistent_len = min(min_consistent_len,
						server->consistent_length);
		}
		if(server->contains_inconsistency)
			*sawInconsistency = TRUE;
	}
	*consistency_len = min_consistent_len;
}
*/

// print all information received from probe servers
void print_probe_info(SSHNotary *notary) {
	struct timeval t;
	gettimeofday(&t,NULL);
	int cur_secs = t.tv_sec;

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
		
			int i;
			for(i = 0; i < list_elem->num_probes; i++) {
				uint32_t ip_addr = list_elem->addresses[i];
				char* ip_str = inet_ntoa(*(struct in_addr*)
					&ip_addr);
				int diff = cur_secs - list_elem->timestamps[i];
				printf("ip = %s (%.1f days ago) \n", ip_str, 
					SEC2DAY(diff));
			}
		}
	
	}
}

// loads a file where probe servers are listed one per line:
// <server ip> <server port> 
// (no per-probe server public keys yet) 
void load_probe_servers(SSHNotary *notary, char* fname){
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
		add_probe_server(notary, ip_addr, port);
	
	}
}
