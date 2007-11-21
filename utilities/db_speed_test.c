
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
            int r = get_data(db, all_hosts[i], buf, 4000);
            if(r < 0) ++failures;
        }
        
        gettimeofday(&end,NULL);
        float sec_diff = (float) (end.tv_sec - start.tv_sec);
        int usec_diff = end.tv_usec - start.tv_usec;
        float usec_fraction = ((float)(usec_diff))/(1000000.0);
        float time_result = sec_diff + usec_fraction;
        printf("For %d lookups, %f seconds \n",
            actual, time_result);

        printf("%d failures \n", failures);
}

unsigned int notary_debug = DEBUG_ERROR;

int main(int argc, char** argv)
{

      if(argc != 3) {
        printf("usage: <db-filename> <count> \n");
        exit(1);
      }
      struct timeval now;
      gettimeofday(&now,NULL);


      DB* db = bdb_open(argv[1], DB_CREATE);
  

      warm_db(db);
      
      read_speed_test(db, atoi(argv[2]));
      
      bdb_close(db);
      return 0;
}

