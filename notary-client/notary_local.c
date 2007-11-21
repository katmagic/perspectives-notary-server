#include <sys/types.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "common.h"
#include "debug.h"
#include "notary_crypto.h"
#include "notary_util.h"
#include "net_util.h"
#include "notary_local.h"


ssh_key_info_list* parse_message(char *buf, int msg_len, RSA* pub_key) {
   notary_header *hdr = (notary_header*)buf;
   int hdr_len = HEADER_SIZE(hdr);
   char *serviceid = (char*) (hdr + 1);
   DPRINTF(DEBUG_INFO, "Reply for serviceid = '%s' \n", serviceid);
   char *data = ((char*)buf) + hdr_len;
   int total_len = ntohs(hdr->total_len);
   if(total_len != msg_len) {
      DPRINTF(DEBUG_ERROR, "Length mismatch header = %d actual = %d \n",
                              total_len, msg_len);
      return NULL;
   }
   int data_len = total_len - hdr_len;
   if(!verify_message_signature(hdr, pub_key)) {
      DPRINTF(DEBUG_ERROR, "**** Signature is invalid **** \n");
      return NULL;
   }

   return list_from_data(data, data_len, SIGNATURE_LEN);
}



// caller should free memory
notary_header* create_request(char*hostname, uint16_t service_type) {
        int name_len = strlen(hostname) + 1;
        int total_len = sizeof(notary_header) + name_len;
        notary_header* hdr = (notary_header*)malloc(total_len);
        hdr->version = 1;
        hdr->msg_type = TYPE_FETCH_REQ;
        hdr->total_len = htons(total_len);
        hdr->name_len = htons(name_len);
        hdr->service_type = htons(service_type);
	char* name_start = (char*)(hdr+1);
	memcpy(name_start, hostname, name_len);
        return hdr;
}

void add_notary_server(SSHNotary *notary, uint32_t ip_address, uint16_t port, 
                              RSA* key){
	server_list *tmp = (server_list*)malloc(sizeof(server_list));
	tmp->ip_addr = ip_address;
        tmp->notary_results = NULL; // this is set after data is received + parsed 
        tmp->port = port;
        tmp->public_key = key;
	tmp->received_reply = 0;
        tmp->consistent_secs = 0;
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
// or when a new host is being checked
void free_key_info(SSHNotary* notary) {

	server_list *server;
	struct list_head *pos;
	list_for_each(pos,&notary->notary_servers.list){
		server = list_entry(pos, server_list, list);
                        
                free_key_info_list(server->notary_results); 
        }
}
 
void free_ssh_notary(SSHNotary* notary){
	free_key_info(notary); // call before freeing server info

	server_list *server;
	struct list_head *pos, *q;
	list_for_each_safe(pos, q, &notary->notary_servers.list){
		server = list_entry(pos, server_list, list);
                RSA_free(server->public_key);
		list_del(&server->list);
		free(server);
	}
	free(notary);
}

// expects the port in host byte order, the ip address in network byte order
// (i.e., as stored in the server struct) 
server_list * find_server(SSHNotary* notary, uint32_t server_ip, uint16_t server_port){
	free_key_info(notary); // call before freeing server info

	server_list *server;
	struct list_head *pos, *q;
	list_for_each_safe(pos, q, &notary->notary_servers.list){
		server = list_entry(pos, server_list, list);
                if(server->ip_addr == server_ip && 
                    server->port == server_port)
                  return server;
	}
	return NULL;
}


// print all information received from probe servers
void print_notary_reply(SSHNotary *notary) {
	server_list *server;
	struct list_head *outer_pos;
	list_for_each(outer_pos,&notary->notary_servers.list){
		server = list_entry(outer_pos, server_list, list);

		printf("***********  Probes from server %s ********** \n", 
			inet_ntoa(*(struct in_addr*)&server->ip_addr));
		
		print_key_info_list(server->notary_results);
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

/*
 * We don't use this anymore, as we now include public keys in the 
 * same file
 *
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
*/


#define PEM_PUB_START "-----BEGIN PUBLIC KEY-----\n"
#define PEM_PUB_END "-----END PUBLIC KEY-----\n"

int read_single_pubkey(FILE *f, char *buf, int max_len) {

        int offset = 0;
        char line[1024];
        BOOL key_started = FALSE; 
	while(fgets(line, 1024, f) != NULL) {
            if(strcmp(PEM_PUB_START, line) == 0)
              key_started = TRUE;

            if(!key_started) 
              continue;

            int line_len = strlen(line);
            if(offset + line_len > max_len){
              DPRINTF(DEBUG_ERROR, "error, pubkey file larger than buf \n");
              exit(1);
            }
            // don't copy null terminator
            memcpy(buf + offset, line, line_len);
            offset += line_len;

            if(strcmp(PEM_PUB_END, line) == 0)
              return offset;
        }
        DPRINTF(DEBUG_ERROR, "Error: reached EOF before finished reading key \n");
        exit(1);
        return -1; // shutup compiler
}

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
	 
		uint32_t ip_addr = str_2_ip(buf);
		int port = (uint16_t) atoi(delim + 1);
                char buf[1024];
                int key_file_len = read_single_pubkey(f, buf, 1024);
                RSA * pub_key = key_from_buf(buf, key_file_len, FALSE);
                DPRINTF(DEBUG_INFO, "loaded key for server '%s' : %d \n", 
                          ip_2_str(ip_addr), port);
		add_notary_server(notary, ip_addr, port, pub_key);
	}
}

/*  debug main
 *
unsigned int notary_debug = DEBUG_ERROR;

int main(int argc, char **argv) {

  SSHNotary *notary = init_ssh_notary();
  load_notary_servers(notary, "notary_list.txt");
  printf("notary results: \n");
  print_notary_reply(notary);
  free_ssh_notary(notary);
  return 0;
}

*/

