#ifndef _CONTACT_PROBE_SERVER_H_
#define _CONTACT_PROBE_SERVER_H_

#include "../common.h"

void contact_probe_server (notary_header *hdr, int msg_len, 
		SSL *ssl_connection); 
SSL * getSSLConnection(char *remote_ip, uint16_t remote_port);

#endif
