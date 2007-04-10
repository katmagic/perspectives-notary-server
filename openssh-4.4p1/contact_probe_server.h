#ifndef _CONTACT_PROBE_SERVER_H_
#define _CONTACT_PROBE_SERVER_H_

#include "../common.h"
#include "notary_local.h"
#include <openssl/ssl.h>

static int int_compare(const void* x, const void *y) {
	return (*(int*)x) - (*(int*)y);
}

void contact_probe_servers(server_list* servers, char *host_name, 
	uint16_t key_type, uint16_t service_port, char* cert_file);


#endif
