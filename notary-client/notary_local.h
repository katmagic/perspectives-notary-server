#ifndef _NOTARY_LOCAL_H_
#define _NOTARY_LOCAL_H_

#include <openssl/ssl.h>
#include <openssl/rsa.h>
#include "../common/common.h"


#define NOTARY_NOT_CONSISTENT -1

typedef struct {
	struct list_head list;
	
	// server info
	uint32_t ip_addr;
	uint16_t port;
        RSA* public_key; 

	// result data
	ssh_key_info_list notary_results;
	uint8_t contact_succeeded;
	
} server_list;

typedef struct {
	server_list notary_servers;
} SSHNotary;

void probe_for_key(SSHNotary *notary, int time_out_msecs,
		char *name, uint16_t service_type, 
		uint16_t service_port);


SSHNotary* init_ssh_notary(); 
void free_ssh_notary(SSHNotary* notary); 

void load_notary_servers(SSHNotary *notary, char* fname);
void add_notary_server(SSHNotary *notary, uint32_t ip_address, uint16_t port);

void print_probe_info(SSHNotary *notary);
void print_probe_info2(SSHNotary *notary);

#endif
