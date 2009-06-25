
#include "common.h" 


#define FINISHED_CHILD_SOCK_NAME "probe_finished_reply"
#define NEW_REQUEST_SOCK_NAME "probe_request"

void record_key(char *dns_name, uint32_t ip_addr, uint16_t port,
                  uint8_t* digest, uint32_t digest_len, uint32_t key_type,  
		  char *server_version_string, uint8_t service_type);
