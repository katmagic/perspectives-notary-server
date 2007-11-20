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

    printf("Querying with regex '%s', limit of %d total results \n",
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
        printf("error opening cursor\n");
        db->err(db, ret, "Cursor open: ");
        exit(1);
    }

    memset(&key, 0, sizeof(key));
    memset(&data, 0, sizeof(data));
    while((ret = cursorp->get(cursorp,&key,&data, DB_NEXT)) == 0) {
        int match = !regexec(&re, key.data, 0,0,0);
        if(match) {
            printf("Host: '%s' \n", (char*)key.data);
            ssh_key_info_list *list = list_from_data(data.data, data.size,
                                                      SIGNATURE_LEN);
            print_key_info_list(list);
            printf("\n");
            free_key_info_list(list);
            ++matches;
            if(matches == limit) {
                printf("Reached limit of %d results.  Exiting \n", limit);
                cursorp->close(cursorp);
                return;
            }
        }
        ++count;
    }
    printf("done examining %d entries \n", count);

    if(ret != DB_NOTFOUND) {
        printf("some error iterating through db: %s \n",
            db_strerror(ret));
        db->err(db, ret, "DB cursor");
    }

    if(cursorp != NULL)
      cursorp->close(cursorp);

}

DB *db; // global so signal handler can close db.

void close_db(int signal) {
  printf("Closing BDB database \n");
  if(db != NULL)
     bdb_close(db);
  exit(1);
}


int
main(int argc, char** argv)
{

      if(argc != 4) {
        printf("usage: <db-filename> <regular expression> <max results>\n");
        exit(1);
      }

      signal(SIGINT, close_db);

      db = bdb_open(argv[1], DB_CREATE);
      if(db == NULL) {
          printf("bdb_open failed \n");
          exit(1);
      }


      loop_over(db, argv[2], atoi(argv[3]));

      bdb_close(db);
      return 0;
}
