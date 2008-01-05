#ifndef _NOTARY_LOCAL_H_
#define _NOTARY_LOCAL_H_

#include <stdio.h>
#include <openssl/ssl.h>
#include <openssl/rsa.h>
#include "common.h"
#include "notary_crypto.h"

// represents a single notary server and its reply on the 
// client side
typedef struct {
	struct list_head list;
	
	// server info
	uint32_t ip_addr;
	uint16_t port;
        RSA* public_key; 

	// result data
	ssh_key_info_list *notary_results;
	uint8_t received_reply;
        uint32_t consistent_secs;	
} server_list;

// master handle given to client 
typedef struct {
	server_list notary_servers;
        int num_servers;
} SSHNotary;

typedef SSHNotary Notary; 



SSHNotary* init_ssh_notary(); 

void free_ssh_notary(SSHNotary* notary); 

void free_key_info(SSHNotary* notary);

void load_notary_servers(SSHNotary *notary, char* buf, int buf_len);

void load_notary_server_file(SSHNotary *notary, char* fname);

void print_notary_reply(FILE *f, SSHNotary *notary);

notary_header* create_request(char*hostname, uint16_t service_type);

ssh_key_info_list* parse_message(char *buf, int msg_len, RSA* pub_key);

server_list * find_server(SSHNotary* notary, uint32_t server_ip, uint16_t server_port);

char *get_notary_reply(SSHNotary *notary);
int get_number_of_notaries(SSHNotary *notary);


#endif
