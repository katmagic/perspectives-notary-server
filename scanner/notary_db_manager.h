#ifndef _SCAN_DB_MANAGER_H_
#define _SCAN_DB_MANAGER_H_

#include "common.h"
#include <sys/types.h>

typedef struct {
	char *db_env_fname;
	char *db_fname;
        char *private_key_fname;
	char *request_finished_sock;
} scanner_config;




#endif
