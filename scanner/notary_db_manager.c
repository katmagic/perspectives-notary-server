#include <sys/socket.h>
#include <sys/un.h>
#include <sys/wait.h>
#include <sys/signal.h> 

#include "db.h"
#include "bdb_storage.h"
#include "notary_crypto.h"
#include "notary_util.h"
#include "notary_db_manager.h"
#include "keyscan_util.h"
#include "net_util.h"


void parse_config_file(scanner_config *conf, char* fname);

scanner_config config; // global config
unsigned int notary_debug = DEBUG_DEFAULT;


#define DO_SIGNATURE TRUE

DB* db;
RSA *priv_key;

int child_finished_sock;

void close_db(int signal) {
  DPRINTF(DEBUG_ERROR, "Caught signal, closing BDB database env\n");
  if(db != NULL)
     bdb_close_env(db);
  exit(1);
}


void handle_finished_client(int cur_time) {
        
        char buf[4048]; // bug: i had truncated keys b/c of this
        int data_len = readUnixClientData(child_finished_sock, buf, 4048); 
        if(data_len == -1) {
          DPRINTF(DEBUG_ERROR, "Read from finished client failed \n"); 
          return; 
        }

        int name_len = strlen(buf);
        char *version_str = buf + name_len + 1;
        int version_len = strlen(version_str);
        char *ptr = buf + name_len + version_len + 2;
        //uint32_t ip_addr = *(uint32_t*)ptr;
        //unsigned short port = *(unsigned short*) (ptr + 4);
        int key_type = *(int*) (ptr + 6);
        int key_len = data_len - name_len - version_len - 12;
        if(key_len != KEY_LEN) {
          DPRINTF(DEBUG_ERROR, "Finished client gave odd key-len = %d \n",
              key_len); 
          return; 
        }
        char *key_ptr = ptr + 10;
    
        char *str = buf_2_hexstr((char*)key_ptr, key_len);
        DPRINTF(DEBUG_INFO, "'%s' has %s key: '%s' \n", buf, 
            keytype_2_str(key_type), str); 
        free(str);
       
        record_observation(db, priv_key, buf, key_ptr, key_len,
                              key_type, cur_time, DO_SIGNATURE);
}


int main(int argc, char** argv) {

  if(argc != 2) {
      fprintf(stderr, "ERROR: usage: <conf-file> \n");
      exit(1);
  }

  register_for_signals(close_db);
  
  parse_config_file(&config, argv[1]);

  priv_key = load_private_key(config.private_key_fname);

  db = bdb_open_env(config.db_env_fname, g_db_env_flags,
                    config.db_fname, g_db_flags | DB_CREATE);
  warm_db(db);

   // create global UNIX domain server sockets
   // to get replies from other threads
  child_finished_sock = openUnixServerSock(config.request_finished_sock,1000); 
  fd_set readset;
  struct timeval t,now;
  while(1) { 
      t.tv_sec = 1;
      t.tv_usec = 0; 

      FD_ZERO(&readset);
      FD_SET(child_finished_sock, &readset);
      int result = select(child_finished_sock + 1, &readset, NULL, NULL, &t); 

      if(result > 0) {
	gettimeofday(&now,NULL); 
        if(FD_ISSET(child_finished_sock, &readset)) {
          handle_finished_client(now.tv_sec);
        }
      }else if(result < 0) {
        perror("select error: ");
      } 
  }
 
  close(child_finished_sock);
  bdb_close_env(db);
  return 0;
}


// read in name-value pairs from file to specify config
// parameters for the scanner 
void parse_config_file(scanner_config *conf, char* fname){
	char buf[1024];
	FILE *f;
	assert(fname);

	f = fopen(fname, "r");
	if(f == NULL) {
		fprintf(stderr,
		"ERROR: Invalid conf file %s \n", fname);
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
		if(strcmp(buf, "db_env_fname") == 0){
			conf->db_env_fname = strdup(value);
		} else if(strcmp(buf, "private_key_fname") == 0){
			conf->private_key_fname = strdup(value);
		} else if(strcmp(buf, "db_fname") == 0) {
			conf->db_fname = strdup(value);
		} else if(strcmp(buf, "request_finished_sock") == 0) {
			conf->request_finished_sock = strdup(value);
		} else {
			DPRINTF(DEBUG_ERROR, "Unknown config value %s : %s \n",
					buf, value);
		}
	}		
}
