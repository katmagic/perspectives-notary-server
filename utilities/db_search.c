#include <sys/types.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <regex.h>

#include "db.h"
#include "common.h"
#include "notary_util.h"
#include "bdb_storage.h"

unsigned int notary_debug = DEBUG_ERROR;

void loop_over(DB *db, char *regex, int limit){
    DBC *cursorp;
    DBT key,data;
    int ret; 

    fprintf(stderr, "INFO: Querying with regex '%s', limit of %d total results \n",
                    regex, limit);

    regex_t re;
    int res = regcomp(&re, regex, REG_EXTENDED);
    if(res) {
        char tmp[128];
        regerror(res, &re, tmp, sizeof(tmp));
        DPRINTF(DEBUG_ERROR, "regex error: %s \n", tmp);
        regfree(&re);
        return;
    }

    int count = 0;
    int matches = 0;
    ret = db->cursor(db, NULL, &cursorp,0);
    if(ret) {
        fprintf(stderr, "ERROR: error opening cursor\n");
        db->err(db, ret, "ERROR: Cursor open");
        exit(1);
    }

    memset(&key, 0, sizeof(key));
    memset(&data, 0, sizeof(data));
    while((ret = cursorp->get(cursorp,&key,&data, DB_NEXT)) == 0) {
        int match = !regexec(&re, key.data, 0,0,0);
        if(match) {
            printf("\n");
            printf("Start Host: '%s' \n", (char*)key.data);
            printf("\n");
            ssh_key_info_list *list = list_from_data(data.data, data.size,
                                                      SIGNATURE_LEN);
            print_key_info_list(stdout, list);
            printf("End Host\n");
            printf("\n");
            free_key_info_list(list);
            ++matches;
            if(matches == limit) {
                fprintf(stderr, "WARNING: Reached limit of %d results.  Exiting \n", limit);
                cursorp->close(cursorp);
                return;
            }
        }
        ++count;
    }
    fprintf(stderr, "INFO: done examining %d entries \n", count);

    if(ret != DB_NOTFOUND) {
        fprintf(stderr, "ERROR: some error iterating through db: %s \n",
            db_strerror(ret));
        db->err(db, ret, "ERROR: DB cursor");
    }

    if(cursorp != NULL)
      cursorp->close(cursorp);

}

DB *db; // global so signal handler can close db.

void close_db(int signal) {
  fprintf(stderr, "WARNING: Caught signal, closing BDB database environment\n");
  if(db != NULL)
     bdb_close_env(db);
  exit(1);
}


int
main(int argc, char** argv)
{

      if(argc != 5) {
        fprintf(stderr, "ERROR: usage: <db-env-filename> <db-filename> <regular expression> <max results>\n");
        exit(1);
      }

      register_for_signals(close_db); 

      db = bdb_open_env(argv[1], g_db_env_flags, argv[2], 
				DB_RDONLY);
      if(db == NULL) {
          fprintf(stderr, "ERROR: bdb_open failed \n");
          exit(1);
      }


      loop_over(db, argv[3], atoi(argv[4]));

      bdb_close_env(db);
      return 0;
}
