#include <stdint.h>
typedef struct {
	uint16_t port;
	uint32_t ip_addr;
	char *db_env_fname;
	char *db_fname;
	char *new_request_sock; 
} server_config;

void request_ondemand_probe(char * service_id,char* sockname); 

void parse_config_file(server_config *conf, char* fname);
