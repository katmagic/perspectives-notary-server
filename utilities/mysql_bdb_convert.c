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

#define NUM_LOOKUPS 10000



// uses old mysql database to create the full 'data' content
// that we want to put in the new database (i.e., the whole 
// packet except for the header and the hostname
int create_db_content(MYSQL *mysql, char* buf, unsigned int buf_size,
                                          char *hostname) {

  char sig_buf[256];
  int sid;
  unsigned int sig_len;
  
  
  get_sid_and_sig(mysql, hostname, sig_buf, &sig_len, &sid);

  int size = get_reply_data(mysql,sid , buf, buf_size);

  if(sig_len + size > buf_size) {
      printf("oops, no room for the signature \n");
      return -1;
  }
  memcpy(buf + size, sig_buf, sig_len);

  return sig_len + size;
}

// transfer entries from the old MYSQL format to 
// a BDB database
void insert_service_entries(DB *db, int dup_factor) {
  
        MYSQL *mysql = open_mysql_conn("localhost","root",
                                  "moosaysthecow","ssh");
        MYSQL *mysql2 = open_mysql_conn("localhost","root",
                                  "moosaysthecow","ssh");

        char query_buf[128];
        snprintf(query_buf, 128, 
          "SELECT dns_name from service_id order by RAND()");

	int error_code = 
		mysql_real_query(mysql2, query_buf, strlen(query_buf));
	if(error_code) {
		fprintf(stderr, "Error looking up key: %s \n",
			mysql_error(mysql));
		exit(1);
        }
        char buf[4000];
        char name_buf[256];

	MYSQL_RES* result = mysql_store_result(mysql2);
	
        int total = 0;

        MYSQL_ROW row; 
        while((row = mysql_fetch_row(result)) != NULL) {

            if(row[0] == NULL){
              break;
            }
            snprintf(name_buf, 256, "%s:22", row[0]);
            int size = create_db_content(mysql, buf, 
                          4000, row[0]);
            if(size <= 0)
              continue;
    
            if(dup_factor == 0){
              store_data(db, name_buf, buf, size);
            }else {
              int i;
              char key_buf[256];
              for(i = 0;i < dup_factor; i++) {
                  snprintf(key_buf, 256, "%s%d", name_buf, i);
                  buf[2] = i; // just to make each record different
                  store_data(db,key_buf, buf, size);
                  ++total;
                  if((total % 1000) == 0)
                    printf("total = %d \n", total);
              }
            }
        }

        db->close(db, 0);
        mysql_free_result(result);
        close_mysql_conn(mysql);
        close_mysql_conn(mysql2);
        exit(1);
}

char ** get_random_hoststrings(int num) {
        char **all_hosts = (char**)malloc(sizeof(char*) * num);

        MYSQL *mysql2 = open_mysql_conn("localhost","root",
                                  "moosaysthecow","ssh");

        char query_buf[128];
        snprintf(query_buf, 128, 
          "SELECT dns_name from service_id order by RAND() limit %d",
          NUM_LOOKUPS);

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
            int len = strlen(row[0]) + 5;
            all_hosts[i] = (char*)malloc(len);
            snprintf(all_hosts[i], len, "%s:22",row[0]);
        }
        printf("Read %d names from MySQL \n", i);
        return all_hosts;
}



void read_speed_test(DB *db) {
  
        char **all_hosts = get_random_hoststrings(NUM_LOOKUPS);

        warm_db(db);

        char buf[4000];
        struct timeval start, end;
        gettimeofday(&start,NULL);

        int failures = 0;
        int i;
        for(i = 0; i < NUM_LOOKUPS; i++) {
            int r = get_data(db, all_hosts[i], buf, 4000);
            if(r < 0) ++failures;
        }
        
        gettimeofday(&end,NULL);
        float sec_diff = (float) (end.tv_sec - start.tv_sec);
        int usec_diff = end.tv_usec - start.tv_usec;
        float usec_fraction = ((float)(usec_diff))/(1000000.0);
        float time_result = sec_diff + usec_fraction;
        printf("For %d lookups, %f seconds \n",
            NUM_LOOKUPS, time_result);

        printf("%d failures \n", failures);
}

void write_speed_test(DB *db) {
  
        char **all_hosts = get_random_hoststrings(NUM_LOOKUPS);


        char buf[4000];
        struct timeval start, end;
        gettimeofday(&start,NULL);

        int failures = 0;
        int i;
        for(i = 0; i < NUM_LOOKUPS; i++) {
            int size = get_data(db, all_hosts[i], buf, 4000);
            if(size < 0) ++failures;

            memset(buf, 'A', size + 20);
            int result = store_data(db, all_hosts[i], buf, size + 20);
            if(result != 0) ++failures;

        }
        
        gettimeofday(&end,NULL);
        float sec_diff = (float) (end.tv_sec - start.tv_sec);
        int usec_diff = end.tv_usec - start.tv_usec;
        float usec_fraction = ((float)(usec_diff))/(1000000.0);
        float time_result = sec_diff + usec_fraction;
        printf("For %d lookup/modify/writes, %f seconds \n",
            NUM_LOOKUPS, time_result);

        printf("%d failures \n", failures);
}

int
main(int argc, char** argv)
{

      if(argc != 2) {
        printf("usage: <db-filename>\n");
        exit(1);
      }

      DB* db = bdb_open(argv[1], DB_CREATE);

   //
   // this call creates a new berkeley DB based on a
   // MySQL DB
   //
   //insert_service_entries(db, 20);

   //  these are simple microbenchmarks
   // 
   //  read_speed_test(db);
   //  write_speed_test(db);
   //
       printf("doing nothing for now \n");

      bdb_close(db);
      return 0;
}
