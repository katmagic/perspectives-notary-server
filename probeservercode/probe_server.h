#ifndef _PROBE_SERVER_H_
#define _PROBE_SERVER_H_

#include "key.h" // from ssh code

typedef struct {
	char *name;
	uint16_t port;
	uint32_t ip;
	Key * key;	
} ssh_key_holder;


#endif
