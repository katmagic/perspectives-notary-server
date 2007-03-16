#ifndef _CONTACT_PROBE_SERVER_H_
#define _CONTACT_PROBE_SERVER_H_

#include "../common.h"
#include <openssl/ssl.h>


ssh_key_info* get_key_info_ssh(ssh_msg_list *head,  uint32_t pserver_ip, 
	uint16_t pserver_port, char *host_name, 
	uint16_t host_port, uint16_t key_type);


#endif
