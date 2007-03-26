#ifndef _CONTACT_PROBE_SERVER_H_
#define _CONTACT_PROBE_SERVER_H_

#include "../common.h"
#include <openssl/ssl.h>

static int int_compare(const void* x, const void *y) {
	return (*(int*)x) - (*(int*)y);
}

void get_key_info_ssh(ssh_result_list *head,  uint32_t pserver_ip, 
	uint16_t pserver_port, char *host_name, 
	uint16_t host_port, uint16_t key_type, char* cert_file);


#endif
