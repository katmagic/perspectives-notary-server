
#include <stdlib.h>
#include <signal.h>
#include "db.h"
#include "common.h"
#include "bdb_storage.h"
#include "notary_util.h"

unsigned int notary_debug = DEBUG_ERROR;

// global so signal handler can close db and file.
DB *db; 
FILE *f;

void loop_over(){
    DBC *cursorp;
    DBT key,data;
    int ret; 

    ret = db->cursor(db, NULL, &cursorp,0);
    if(ret) {
        printf("error opening cursor\n");
        db->err(db, ret, "Cursor open: ");
        exit(1);
    }

    memset(&key, 0, sizeof(key));
    memset(&data, 0, sizeof(data));
    while((ret = cursorp->get(cursorp,&key,&data, DB_NEXT)) == 0) {
      fprintf(f, "Start Host: '%s' \n", (char*)key.data);
      ssh_key_info_list *list = list_from_data(data.data, data.size,
                                                      SIGNATURE_LEN);
      print_key_info_list(f, list);
      fprintf(f, "End Host\n");
      free_key_info_list(list);
    }

    if(ret != DB_NOTFOUND) {
        printf("some error iterating through db: %s \n",
            db_strerror(ret));
        db->err(db, ret, "DB cursor");
    }

    if(cursorp != NULL)
      cursorp->close(cursorp);

}


void close_db(int signal) {
  printf("Closing BDB database \n");
  if(db != NULL)
     bdb_close(db);
  if(f != NULL)
    fclose(f);
  exit(1);
}


int main(int argc, char** argv) {
                 
      if(argc != 3) {
        printf("usage: <db-in> <file-out> \n");
        exit(1);
      }

      signal(SIGINT, close_db);

      db = bdb_open(argv[1], DB_CREATE);
      if(db == NULL) {
          printf("bdb_open failed \n");
          exit(1);
      }


      f = fopen(argv[2], "w");
      loop_over();

      bdb_close(db);
      fclose(f);
      return 0;

}
