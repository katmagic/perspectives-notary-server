#ifndef _PROBE_SERVER_H_
#define _PROBE_SERVER_H_

#include "../common.h"
#include "../util/list.h" // modified from linux kernel 
#include "key.h" // from ssh code

// stupid hack needed to get SSH and SSL to play along
#define SSL void

// code that used to be in probe_server.h


typedef struct {
	struct list_head list;
	int sock;
	int offset; 
	void* ssl;
	char buf[MAX_PACKET_LEN];
} conn_node;

typedef struct {
	char *name;
	uint16_t port;
	uint16_t key_type;
	uint32_t ip_addr;	
	Key * key;
	conn_node* conn;
        char version_str[64];
} ssh_key_holder;



#endif
