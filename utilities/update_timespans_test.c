#include <sys/types.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "db.h"
#include "common.h"

#include "mysql.h"
#include "common.h"
#include "notary_crypto.h"
#include "mysql_storage.h"
#include "notary_util.h"
#include "bdb_storage.h"

unsigned int notary_debug = DEBUG_ERROR;





char ** get_random_hoststrings(int num) {
        char **all_hosts = (char**)malloc(sizeof(char*) * num);

        MYSQL *mysql2 = open_mysql_conn("localhost","root",
                                  "moosaysthecow","ssh");

        char query_buf[128];
        snprintf(query_buf, 128, 
          "SELECT dns_name from service_id order by RAND() limit %d",
          num);

	int error_code = 
		mysql_real_query(mysql2, query_buf, strlen(query_buf));
	if(error_code) {
		fprintf(stderr, "Error looking up key: %s \n",
			mysql_error(mysql2));
		exit(1);
        }

	MYSQL_RES* result = mysql_store_result(mysql2);
	
        int i;
        MYSQL_ROW row;
        for(i = 0; i < num; i++) {

            row = mysql_fetch_row(result);

            if(row == NULL || row[0] == NULL){
              printf("early null at i = %d \n", i);
              exit(1);
            }
            int len = strlen(row[0]) + 4;
            all_hosts[i] = (char*)malloc(len);
            snprintf(all_hosts[i], len, "%s:22",row[0]);

        }
        printf("Read %d names from MySQL \n", i);
        return all_hosts;
}



void read_speed_test(DB *db, int count) {
  
        char **all_hosts = get_random_hoststrings(count);

        warm_db(db); 

        char buf[4000];
        struct timeval start, end;
        gettimeofday(&start,NULL);

        int failures = 0;
        int i;
        for(i = 0; i < count; i++) {
            int r = get_data(db, all_hosts[i], buf, 4000);
            if(r < 0) ++failures;
        }
        
        gettimeofday(&end,NULL);
        float sec_diff = (float) (end.tv_sec - start.tv_sec);
        int usec_diff = end.tv_usec - start.tv_usec;
        float usec_fraction = ((float)(usec_diff))/(1000000.0);
        float time_result = sec_diff + usec_fraction;
        printf("For %d lookups, %f seconds \n",
            count, time_result);

        printf("%d failures \n", failures);
}

int  get_a_public_key(DB* db, char* service_id,
                              char *buf_out, uint8_t* key_type_out){

        char buf[MAX_PACKET_LEN];
        int data_size = get_data(db, service_id, buf, MAX_PACKET_LEN);
        if(data_size < 0) {
            printf("Error retrieving data for: %s\n", service_id);
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


int make_timespan_change(DB* db, RSA *priv_key,
                      char *service_id, int timestamp) {

      char key_buf[SIGNATURE_LEN];
      uint8_t key_type;
      int key_len;
      /*
      key_len = get_a_public_key(db, service_id,key_buf,&key_type);
      if(key_len <= 0) {
          printf("invalid key len = %d \n", key_len);
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
                                  timestamp);

/*     // uncomment this call to test 'add new timespan' case
       // must also comment out memset above
      record_observation(db, priv_key, service_id, 
                                  key_buf, key_len, key_type,
                                  timestamp + 100);
*/
    return 0;
}

int
main(int argc, char** argv)
{

      if(argc != 2) {
        printf("usage: <db-filename> \n");
        exit(1);
      }
      struct timeval now;
      gettimeofday(&now,NULL);


      DB* db = bdb_open(argv[1], DB_CREATE);
  
      RSA *priv_key = load_private_key("private.pem");

      int count = 1000;
      char** all_hosts = get_random_hoststrings(count);
      int i;

      int failures = 0;
      //warm_db(db);
      printf("TODO: warm db cache!\n");

        struct timeval start, end;
        gettimeofday(&start,NULL);
      
      for(i = 0; i < count;i++) {
         if(make_timespan_change(db,priv_key,all_hosts[i],now.tv_sec))
           ++failures;
      }
        gettimeofday(&end,NULL);
        float sec_diff = (float) (end.tv_sec - start.tv_sec);
        int usec_diff = end.tv_usec - start.tv_usec;
        float usec_fraction = ((float)(usec_diff))/(1000000.0);
        float time_result = sec_diff + usec_fraction;
        printf("For %d lookups, %f seconds \n",
            count - failures, time_result);

        printf("failures: %d \n", failures);
      bdb_close(db);
      return 0;
}
