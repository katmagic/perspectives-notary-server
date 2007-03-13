#ifndef _NOTARY_LOCAL_H_
#define _NOTARY_LOCAL_H_

#include "../common.h"


typedef struct {
	struct list_head list;
	uint32_t ip_addr;
	uint16_t port;
} server_list;

typedef struct {
	server_list probe_servers;	
} SSHNotary;

void check_ssh_key(SSHNotary *notary, char *name, uint16_t service_type, 
		uint16_t service_port, Key *key);
void add_probe_server(SSHNotary *notary, uint32_t ip_address, uint16_t port);

SSHNotary* init_ssh_notary(); 
void free_ssh_notary(SSHNotary* notary); 

void load_probe_servers(SSHNotary *notary, char* fname);

#endif
