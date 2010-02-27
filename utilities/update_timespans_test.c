#include <sys/types.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "db.h"
#include "common.h"
#include "notary_crypto.h"
#include "notary_util.h"
#include "bdb_storage.h"
#include "benchmark_util.h"

unsigned int notary_debug = DEBUG_DEFAULT;

/*
int  get_a_public_key(DB* db, char* service_id,
                              char *buf_out, uint8_t* key_type_out){

        char buf[MAX_PACKET_LEN];
        int data_size = get_data(db, service_id, buf, MAX_PACKET_LEN);
        if(data_size < 0) {
            fprintf(stderr, "ERROR: Error retrieving data for: %s\n", service_id);
            return -1;
        }
        ssh_key_info_list *info_list = 
          list_from_data(buf,data_size, SIGNATURE_LEN);
       
       if(info_list == NULL) {
          return -1;
       }
       struct list_head *pos,*tmp;
       ssh_key_info_list* cur = NULL;

       list_for_each_safe(pos, tmp, &info_list->list) {
            cur = list_entry(pos, ssh_key_info_list, list);    
            break;
       }
       if(cur == NULL) {
          return -1;
       }
       int len = ntohs(cur->info->key_len_bytes);
       char *key_buf = (char*)(cur->info + 1);
       memcpy(buf_out, key_buf, len);
       *key_type_out = cur->info->key_type;
       return len;
}
*/

int make_timespan_change(DB* db, RSA *priv_key,
                      char *service_id, int timestamp) {

      char key_buf[SIGNATURE_LEN];
      uint8_t key_type;
      int key_len;
      /*
      key_len = get_a_public_key(db, service_id,key_buf,&key_type);
      if(key_len <= 0) {
          fprintf(stderr, "ERROR: invalid key len = %d \n", key_len);
          return 1;
      }
      */

      key_len = 16;
      key_type = 1;

      // intentially create a different key
      // tests 'new key' case
      memset(key_buf, 1, key_len); 
      
      // calling this alone tests the 'update timespan' case
      record_observation(db, priv_key, service_id, 
                                  key_buf, key_len, key_type,
                                  timestamp, TRUE);

/*     // uncomment this call to test 'add new timespan' case
       // must also comment out memset above
      record_observation(db, priv_key, service_id, 
                                  key_buf, key_len, key_type,
                                  timestamp + 100);
*/
    return 0;
}

DB *db = NULL; 

void close_db(int signal) {
  fprintf(stderr, "WARNING: Caught signal, closing BDB database environment\n");
  if(db != NULL)
     bdb_close_env(db);
  exit(1);
}

int
main(int argc, char** argv)
{

      if(argc != 4) {
        fprintf(stderr, "ERROR: usage: <db-env-directory> <db-filename> <priv-key-fname>\n");
        exit(1);
      }
      struct timeval now;
      gettimeofday(&now,NULL);

      db = bdb_open_env(argv[1], g_db_env_flags,
                    argv[2], DB_CREATE);
      
      register_for_signals(close_db); 
  
      RSA *priv_key = load_private_key(argv[3]);

      int count = 1000;
      int actual; 
      char **all_hosts = get_random_serviceids(count, db, &actual);
      int i;

      int failures = 0;
      //warm_db(db);
      fprintf(stderr, "TODO: warm db cache!\n");

        struct timeval start, end;
        gettimeofday(&start,NULL);
      
      for(i = 0; i < actual;i++) {
         if(make_timespan_change(db,priv_key,all_hosts[i],now.tv_sec))
           ++failures;
      }
        gettimeofday(&end,NULL);
        float sec_diff = (float) (end.tv_sec - start.tv_sec);
        int usec_diff = end.tv_usec - start.tv_usec;
        float usec_fraction = ((float)(usec_diff))/(1000000.0);
        float time_result = sec_diff + usec_fraction;
        fprintf(stderr, "INFO: For %d lookups, %f seconds \n",
            actual - failures, time_result);

        fprintf(stderr, "INFO: failures: %d \n", failures);
      bdb_close_env(db);
      return 0;
}
