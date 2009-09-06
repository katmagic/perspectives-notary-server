
#include <stdlib.h>
#include <signal.h>
#include "db.h"
#include "common.h"
#include "bdb_storage.h"
#include "notary_util.h"
#include "flex_queue.h"
#include "notary_crypto.h"

unsigned int notary_debug = DEBUG_ERROR;

// global so signal handler can close db and file.
DB *db; 
FILE *f;


#define MAX_DATA_SIZE 10000
#define KEY_DATA_SIZE 16

void parse_file(RSA* priv_key, char* sig_type){
  char buf[1024];

  char hostname[512];

  char data[MAX_DATA_SIZE]; 
  while(fgets(buf, 1024,f) != NULL) {

    int ret = sscanf(buf, "Start Host: '%s' ", hostname);
    if(ret == EOF) {
      printf("error \n");
      continue;
    }
    if(ret != 1) {
      printf("error, ret = %d \n", ret);
      continue;
    }
    int hostname_len = strlen(hostname);
    hostname[hostname_len - 1] = 0x0; // sscanf misses a single quote
    --hostname_len;
    make_lowercase(hostname, hostname_len); 
    DPRINTF(DEBUG_INFO, "host: '%s' \n", hostname);

    memcpy(data, hostname, hostname_len + 1); // copy null terminator
    int offset = hostname_len + 1;

    // read in key-records until we get reach an 'End Host' line
    while(1) {
      char key[64], key_type[32]; 
      fgets(buf, 1024, f);
      if(strcmp(buf,"End Host\n") == 0) break;

      sscanf(buf, "%s key: %s\n", key_type, key); 
      DPRINTF(DEBUG_INFO, 
          "key-type = '%s'  key = '%s' \n", key_type, key);
      if(strlen(key) > (3 * KEY_DATA_SIZE)) {
        printf("warning, key data is bigger than expected! \n");
      }

      ssh_key_info *k_info = (ssh_key_info*) (data + offset);
      offset += sizeof(ssh_key_info); 
      k_info->key_len_bytes = htons(KEY_DATA_SIZE);
      k_info->key_type = str_2_keytype(key_type);
      if(k_info->key_type == 255) {
        printf("error, bad key-type (%s) for %s \n", 
            key_type, hostname);
      }
      int num_bytes = hexstr_2_buf(key, data + offset, KEY_DATA_SIZE);
      if(num_bytes != KEY_DATA_SIZE) {
        printf("Error, wrong KEY_DATA_SIZE (expected %d got %d from "
            " key = '%s' \n", KEY_DATA_SIZE, num_bytes, key);
        exit(1); 
      }
      offset += KEY_DATA_SIZE; 


      int timespan_count = 0;
      while(1) {

        int start, end; 
        fgets(buf, 1024, f);
        if(*buf == '\n') {
          DPRINTF(DEBUG_INFO, "end of key entry \n");
          break;
        }
        sscanf(buf,"start: %d ", &start);
        fgets(buf, 1024, f);
        sscanf(buf,"end: %d ", &end);
        int net_start = htonl(start);
        memcpy(data + offset, (char*)&net_start, sizeof(int));
        DPRINTF(DEBUG_INFO, "start:\t %d \n", start);
        offset += sizeof(int); 
        int net_end = htonl(end); 
        memcpy(data + offset, (char*)&net_end, sizeof(int));
        DPRINTF(DEBUG_INFO, "end:\t %d \n", end);
        offset += sizeof(int); 
        ++timespan_count;
      } // done while(1) reading in all timespans

      k_info->num_timespans = htons(timespan_count);
    

    } // done while(1) reading all keys for a single host

    if(priv_key != NULL && sig_type != NULL) {
      unsigned char sig_buf[SIGNATURE_LEN];
      unsigned int sig_len;
      int sig_ret; 
      if(strcmp(sig_type, "sha256") == 0) { 
      	sig_ret = get_signature_rsa_sha256(data, offset, 
				priv_key,sig_buf, &sig_len); 
      } else { 
	sig_ret = get_signature(data, offset, priv_key,sig_buf, &sig_len); 
      } 
      if(sig_ret || sig_len != SIGNATURE_LEN) {
        printf("Error calculating signature \n");
        continue; 
      }

      memcpy(data + offset, sig_buf, SIGNATURE_LEN);
    }
    offset += SIGNATURE_LEN; 

    unsigned int data_len = offset - (hostname_len + 1);
    char *data_start = (data + hostname_len + 1);
    DPRINTF(DEBUG_INFO, "data size = %d \n", data_len);
    store_data(db, hostname, data_start, data_len);

    if(offset > MAX_DATA_SIZE) {
      printf("ran out of buffer space converting file to DB \n");
      exit(1); 
    } 

  }  
}


void close_db(int signal) {
  printf("Closing BDB database \n");
  if(db != NULL)
     bdb_close_env(db);
  if(f != NULL)
    fclose(f);
  exit(1);
}


int main(int argc, char** argv) {
                 
//      if(argc != 6 && argc != 4) {
      if(argc != 5 && argc != 4) {
        //printf("usage:<file-in>  <db-env> <db-filename> <priv-key> <md5|sha256>\n");
        printf("usage:<file-in>  <db-env> <db-filename> <priv-key>\n");
        printf("if no private key is given, DB signatures will be invalid\n");
        exit(1);
      }

      register_for_signals(close_db); 
        
      f = fopen(argv[1], "r");
      if(f == NULL) {
        DPRINTF(DEBUG_ERROR, "Couldn't open '%s' \n", argv[1]); 
        exit(1); 
      }

      db = bdb_open_env(argv[2], g_db_env_flags,
                    argv[3], g_db_flags | DB_CREATE);
      
      if(db == NULL) {
          DPRINTF(DEBUG_ERROR, "bdb_open failed for '%s' \n", argv[2]);
          exit(1);
      }

      RSA *priv_key = NULL;
      char *sig_type = NULL; 
      if(argc == 5) {  
        priv_key = load_private_key(argv[4]);
        if(priv_key == NULL) {
          DPRINTF(DEBUG_ERROR, "failed to load private key '%s' \n", argv[3]);
          exit(1);
        }
	sig_type = "md5"; 
      }

      parse_file(priv_key,sig_type); 

      bdb_close_env(db);
      fclose(f);
      return 0;

}
