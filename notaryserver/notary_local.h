#ifndef _NOTARY_LOCAL_H_
#define _NOTARY_LOCAL_H_

#include "../common.h"

static int int_compare(void* x, void*y) {
	return (*(int*)x) - (*(int*)y);
}

typedef struct {
	struct list_head list;
	uint32_t ip_addr;
	uint16_t port;
	ssh_msg_list current_info;	
} server_list;

typedef struct {
	server_list probe_servers;
} SSHNotary;

void contact_probe_servers(SSHNotary *notary, int time_out_msecs,
		char *name, uint16_t service_type, 
		uint16_t service_port);
void add_probe_server(SSHNotary *notary, uint32_t ip_address, uint16_t port);

SSHNotary* init_ssh_notary(); 
void free_ssh_notary(SSHNotary* notary); 

void load_probe_servers(SSHNotary *notary, char* fname);

void print_probe_info(SSHNotary *notary);

#endif
