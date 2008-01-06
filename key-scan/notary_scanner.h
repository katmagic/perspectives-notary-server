#ifndef _NOTARY_SSH_SCANNER_H_
#define _NOTARY_SSH_SCANNER_H_

#include "common.h"
#include <sys/types.h>

typedef struct {
	char *input_fname;
        char *output_fname;
	char *db_env_fname;
	char *db_fname;
	char *exceptions_fname;
        char *private_key_fname;
} scanner_config;


typedef struct {
  pid_t pid;
  char *dns_name;
  uint32_t start_time;
} probe_info;


#endif
