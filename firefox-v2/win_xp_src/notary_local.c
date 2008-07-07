
#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h>

#include "common.h"
#include "debug.h"
#include "notary_local.h"
#include "notary_util.h"
#include "net_util.h"

/*
#include "notary_crypto.h"

*/ 



// warning: for WIN32, this no longer checks the signature
ssh_key_info_list* parse_message(char *buf, int msg_len) {
   notary_header *hdr = (notary_header*)buf;
   int data_len; 
   int hdr_len = HEADER_SIZE(hdr);
   char *serviceid = (char*) (hdr + 1);
   char *data = ((char*)buf) + hdr_len;
   int total_len = ntohs(hdr->total_len);

   DPRINTF(DEBUG_INFO, "Reply for serviceid = '%s' \n", serviceid);
   if(total_len != msg_len) {
      DPRINTF(DEBUG_ERROR, "Length mismatch header = %d actual = %d \n",
                              total_len, msg_len);
      return NULL;
   }
   if(hdr->msg_type == TYPE_FETCH_REPLY_EMPTY) {
      DPRINTF(DEBUG_INFO, "Server found no service-record \n"); 
      return NULL; 
   }
   data_len = total_len - hdr_len;
   return list_from_data(data, data_len, SIGNATURE_LEN);
}





// caller should free memory
notary_header* create_request(char*hostname, uint16_t service_type) {
		char *name_start;
        int name_len = strlen(hostname) + 1;
        int total_len = sizeof(notary_header) + name_len;
        notary_header* hdr = (notary_header*)malloc(total_len);
        hdr->version = 1;
        hdr->msg_type = TYPE_FETCH_REQ;
        hdr->total_len = htons(total_len);
        hdr->name_len = htons(name_len);
        hdr->service_type = htons(service_type);
		name_start = (char*)(hdr+1);
		memcpy(name_start, hostname, name_len);
        make_lowercase(name_start, name_len - 1); // notary only deals with lower-case
        return hdr;
}

void add_notary_server(SSHNotary *notary, uint32_t ip_address, uint16_t port, char *base64_key){
	server_list *tmp = (server_list*)malloc(sizeof(server_list));
	tmp->ip_addr = ip_address;
    tmp->notary_results = NULL; // this is set after data is received + parsed 
    tmp->port = port;
    tmp->public_key = strdup(base64_key);
	tmp->received_reply = 0;
    tmp->consistent_secs = 0;
	__list_add(&tmp->list,&(notary->notary_servers.list),
                            (notary->notary_servers.list.next));
	DPRINTF(DEBUG_INFO, "Adding notary server: %s : %d \n",
			inet_ntoa(*(struct in_addr*)&ip_address), tmp->port);
        ++(notary->num_servers);
}

SSHNotary* init_ssh_notary(){

	SSHNotary *n = (SSHNotary*)malloc(sizeof(SSHNotary));
    n->num_servers = 0;
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
	DPRINTF(DEBUG_INFO, "Freeing key_info data for all servers\n");
	list_for_each(pos,&notary->notary_servers.list){
				server = list_entry(pos, server_list, list);                    
                free_key_info_list(server->notary_results); 
    }
}
 
void free_ssh_notary(SSHNotary* notary){
	server_list *server;
	struct list_head *pos, *q;

	free_key_info(notary); // call before freeing server info
	list_for_each_safe(pos, q, &notary->notary_servers.list){
		server = list_entry(pos, server_list, list);
        if(server->public_key) 
            RSA_free(server->public_key);
		list_del(&server->list);
		free(server);
	}
	free(notary);
}

// expects the port in host byte order, the ip address in network byte order
// (i.e., as stored in the server struct) 
server_list * find_server(SSHNotary* notary, uint32_t server_ip, uint16_t server_port){

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
void print_notary_reply(FILE * f, SSHNotary *notary) {
	server_list *server;
	struct list_head *outer_pos;
	list_for_each(outer_pos,&notary->notary_servers.list){
		server = list_entry(outer_pos, server_list, list);

		printf("***********  Probes from server %s:%d ********** \n", 
			ip_2_str(server->ip_addr), server->port);
		
		print_key_info_list(f, server->notary_results);
	}
}

//Get Notary Reply 
char *get_notary_reply(SSHNotary *notary) {
	server_list *server;
	struct list_head *outer_pos;
        int response_len = 0;
        int max_len = 4096;
        int n = 0;
        // Macro 4096 
        char *response = (char *) malloc(sizeof(char) * max_len);
        if(!response)
        {
            return NULL;
        }
        printf("max_len = %d \n", max_len); 
	list_for_each(outer_pos,&notary->notary_servers.list){
		server = list_entry(outer_pos, server_list, list);
              
		if(response_len >= max_len) { 
			printf("bailing from get_notary_reply \n"); 
			return response; 
		} 
        n = snprintf(response + response_len, max_len - response_len,
                    "***********  Probes from server %s:%d ********** \n", 
		ip_2_str(server->ip_addr), server->port);
	    response_len += n;

		get_key_info_list(response, &response_len, max_len, 
                    server->notary_results);
		printf("after get_key_info_list: response_len = %d max_len = %d\n", response_len,max_len); 
	}
        return response;
}


int get_number_of_notaries(SSHNotary *notary)
{
    return notary->num_servers;
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

// similar to fgets, but for a buffer instead of a file 
char * get_line(char *input_buf, char *output_buf, int buf_size) {
	int len;
    char *end = input_buf; 
    BOOL is_done = FALSE;           
    char *limit = input_buf + buf_size - 2; // need space for \0

    while(*end != '\n' && end != limit) {
       if(*(end++) == EOF){
         is_done = TRUE;        
         break;
      }
    }
    len = (end - input_buf) + 1;
    memcpy(output_buf, input_buf, len);
    output_buf[len] = 0; // null terminate at one past

    return is_done ? NULL : (end + 1); 
}

#define PEM_PUB_START "-----BEGIN PUBLIC KEY-----\n"
#define PEM_PUB_END "-----END PUBLIC KEY-----\n"

char *read_single_pubkey(char *input_buf, char *output_buf, int max_len, int *bytes_read) {

        int offset = 0;
        char line[1024];
        BOOL key_started = FALSE; 
  
        char *ptr = input_buf; 
		while( (ptr = get_line(ptr, line, 1024)) != NULL) {
			int line_len; 
			if(strcmp(PEM_PUB_START, line) == 0){
              key_started = TRUE;
			  continue;
			}
            if(!key_started) 
              continue;

            line_len = strlen(line);
            if(offset + line_len > max_len){
              DPRINTF(DEBUG_ERROR, "error, pubkey file larger than buf \n");
              exit(1);
            }

            if(strcmp(PEM_PUB_END, line) == 0) {
              *bytes_read = offset; 
			  output_buf[offset] = 0x0; 
              return ptr;
            }

            // don't copy null terminator
            memcpy(output_buf + offset, line, line_len);
            offset += line_len;


        }
        DPRINTF(DEBUG_ERROR, "Error: reached EOF before finished reading key \n");
        exit(1);
        return NULL; // shutup compiler
}

#define MAX_FILE_SIZE 100000 
#define MAX_LINE_LENGTH 1024

#ifndef WIN32
// this should be moved to a UNIX specific file

void load_notary_server_file(SSHNotary *notary, char *fname) {
	char buf[MAX_FILE_SIZE];
	FILE *f = fopen(fname, "r");

	if(f == NULL) {
		DPRINTF(DEBUG_ERROR, 
		"Notary Error: Invalid notar-list file %s \n", fname);
		return;
	}
        
        size_t bytes_read = fread(buf, 1, MAX_FILE_SIZE, f);
        if(ferror(f)) {
            DPRINTF(DEBUG_ERROR, "Error reading client config file: %s \n", fname);
            return;
        }

        load_notary_servers(notary, buf, bytes_read);

}

#endif

void load_notary_servers(SSHNotary *notary, char* data, int buf_len){
		RSA* pub_key = 0; 
		int size, port, read_so_far = 0;
		char *delim;
		uint32_t ip_addr;
        char buf[MAX_LINE_LENGTH];
		char buf2[1024];
		int key_len = -1; 

        char *ptr = data;
        char *end = data + buf_len - 1; 
	
	while((ptr = get_line(ptr, buf, MAX_LINE_LENGTH)) != NULL 
            && ptr < end) {
		
		if(*buf == '\n') continue;
		if(*buf == '#') continue;
		size = strlen(buf);
		buf[size - 1] = 0x0; // replace '\n' with NULL
		delim = strchr(buf,' ');
		if(delim == NULL) {
			DPRINTF(DEBUG_ERROR, 
				"Ignoring malformed line: %s \n", buf);
			continue;
		}
		*delim = 0x0;
	 
		 
		
		ip_addr = str_2_ip(buf);
		port = htons((uint16_t) atoi(delim + 1));
        ptr = read_single_pubkey(ptr, buf2, 1024, &key_len);

		printf("got single key = '%s' \n", buf2); 
		/* 
	    WIN32 changes how keys are stored, using base64 encoded PEM, 
		instead of an RSA* struct.
		We need to reconcile that to recombine the files.  
        RSA * pub_key = key_from_buf(buf2, key_len, FALSE);
		*/
		DPRINTF(DEBUG_INFO, "loaded key for server '%s' : %d \n", ip_2_str(ip_addr), port);
		add_notary_server(notary, ip_addr, port, buf2);

	}
}
  
#ifndef WIN32

void parse_client_config(client_config *conf, char *fname){ 
	char buf[1024];
	FILE *f;

	f = fopen(fname, "r");
	if(f == NULL) {
		DPRINTF(DEBUG_ERROR,
		"Notary Error: Invalid conf file %s \n", fname);
		return;
	}

	while(fgets(buf, 1023,f) != NULL) {
		if(*buf == '\n') continue;
		if(*buf == '#') continue;
		int size = strlen(buf);
		buf[size - 1] = 0x0; // replace '\n' with NULL
		char *delim = strchr(buf,'=');
		if(delim == NULL) {
			DPRINTF(DEBUG_ERROR, 
				"Ignoring malformed line: %s \n", buf);
			continue;
		}
		*delim = 0x0;
	 
		char *value = delim + 1;
		DPRINTF(DEBUG_INFO, "key = '%s' value = '%s' \n", 
				buf, value);
		if(strcmp(buf,"debug") == 0) { 
			conf->debug = atoi(value);
		} else if(strcmp(buf, "timeout_secs") == 0) {
			conf->timeout_secs = atof(value);
		} else if(strcmp(buf, "num_notaries") == 0){
			conf->num_notaries = atoi(value);
		} else if(strcmp(buf, "quorum") == 0) {
			conf->quorum = atof(value);
		} else if(strcmp(buf, "quorum_duration_days") == 0) {
			conf->quorum_duration_days = atof(value);
		} else if(strcmp(buf, "max_stale_days") == 0) {
			conf->max_stale_days = atof(value);
		} else {
			DPRINTF(DEBUG_ERROR, "Unknown config value %s : %s \n",
					buf, value);
		}
	}		
}

#endif