#ifndef _SSH_KEYSCAN_H_
#define _SSH_KEYSCAN_H_

// this is a header file for the modified 
// ssh-keyscan, since we are now using it as a 
// library, not as a main() function. 


#include "../common.h"

int do_single_probe(char *host, uint16_t service_type, uint16_t service_port,
		conn_node *conn);
void init_scankeys(); 
int conloop(ssh_key_holder *ssh_keys, int num_holders);



#endif
