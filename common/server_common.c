#include <stdio.h>
#include <string.h>
#include <stdio.h>
#include "server_common.h"
#include "debug.h"
#include "common.h"
#include "net_util.h"

void parse_config_file(server_config *conf, char* fname){
  char buf[1024];
  FILE *f;
  assert(fname);

  f = fopen(fname, "r");
  if(f == NULL) {
    fprintf(stderr,"Notary Error: Invalid conf file %s \n", fname);
    return;
  }

  while(fgets(buf, 1023,f) != NULL) {
    if(*buf == '\n') continue;
    if(*buf == '#') continue;
    int size = strlen(buf);
    buf[size - 1] = 0x0; // replace '\n' with NULL
    char *delim = strchr(buf,'=');
    if(delim == NULL) {
      DPRINTF(DEBUG_ERROR, 
          "Ignoring malformed line: %s \n", buf);
      continue;
    }
    *delim = 0x0;

    char *value = delim + 1;
    DPRINTF(DEBUG_INFO, "key = '%s' value = '%s' \n", 
        buf, value);
    if(strcmp(buf,"ip_addr") == 0) { 
      conf->ip_addr = str_2_ip(value);
    } else if(strcmp(buf, "port") == 0) {
      conf->port = atoi(value);
    } else if(strcmp(buf, "db_env_fname") == 0){
      conf->db_env_fname = strdup(value);
    } else if(strcmp(buf, "db_fname") == 0) {
      conf->db_fname = strdup(value);
    } else {
      DPRINTF(DEBUG_ERROR, "Unknown config value %s : %s \n",
          buf, value);
    }
  }		
}
