
#include "common.h"
#include "bdb_storage.h"
#include "benchmark_util.h"

void read_speed_test(DB *db, int count) {
 
        int actual; 
        char **all_hosts = get_random_serviceids(count, db, &actual);

        warm_db(db); 

        char buf[4000];
        struct timeval start, end;
        gettimeofday(&start,NULL);

        int failures = 0;
        int i;
        for(i = 0; i < actual; i++) {
            int r = get_data(db, all_hosts[i], buf, 4000,0);
            if(r < 0) ++failures;
        }
        
        gettimeofday(&end,NULL);
        float sec_diff = (float) (end.tv_sec - start.tv_sec);
        int usec_diff = end.tv_usec - start.tv_usec;
        float usec_fraction = ((float)(usec_diff))/(1000000.0);
        float time_result = sec_diff + usec_fraction;
        fprintf(stderr, "INFO: For %d lookups, %f seconds \n",
            actual, time_result);

        fprintf(stderr, "INFO: %d failures \n", failures);
}

unsigned int notary_debug = DEBUG_DEFAULT;
DB *db = NULL; 

void close_db(int signal) {
  fprintf(stderr, "WARNING: Caught signal, closing BDB database environment\n");
  if(db != NULL)
     bdb_close_env(db);
  exit(1);
}

int main(int argc, char** argv)
{

      if(argc != 4) {
        fprintf(stderr, "ERROR: usage: <db-env-name> <db-filename> <count> \n");
        exit(1);
      }
      register_for_signals(close_db); 

      db = bdb_open_env(argv[1], g_db_env_flags,
                    argv[2], DB_CREATE);
  
      warm_db(db);
      
      read_speed_test(db, atoi(argv[3]));
      
      bdb_close_env(db);
      return 0;
}

