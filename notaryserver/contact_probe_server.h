#ifndef _CONTACT_PROBE_SERVER_H_
#define _CONTACT_PROBE_SERVER_H_

#include "../common.h"
#include <openssl/ssl.h>

// hold info about one outstanding request
typedef struct {
	struct timeval expires;
	notary_header* hdr;
} probe_pair;

typedef struct {
	SSL* ssl;
	int sock;
} prober_connection;

ssh_key_list* get_key_info_ssh(uint32_t pserver_ip, 
	uint16_t pserver_port, char *host_name, 
	uint16_t host_port, uint16_t key_type);


#endif
