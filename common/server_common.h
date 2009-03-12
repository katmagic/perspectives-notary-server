#include <stdint.h>
typedef struct {
	uint16_t port;
	uint32_t ip_addr;
	char *db_env_fname;
	char *db_fname;
} server_config;

void parse_config_file(server_config *conf, char* fname);
