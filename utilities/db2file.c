
#include <stdlib.h>
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
        fprintf(stderr, "ERROR: error opening cursor\n");
        db->err(db, ret, "ERROR: Cursor open");
        exit(1);
    }

    memset(&key, 0, sizeof(key));
    memset(&data, 0, sizeof(data));
    while((ret = cursorp->get(cursorp,&key,&data, DB_NEXT)) == 0) {
      fprintf(f, "\n");
      fprintf(f, "Start Host: '%s' \n", (char*)key.data);
      fprintf(f, "\n");
      ssh_key_info_list *list = list_from_data(data.data, data.size,
                                                      SIGNATURE_LEN);
      print_key_info_list(f, list);
      fprintf(f, "End Host\n");
      fprintf(f, "\n");
      free_key_info_list(list);
    }

    if(ret != DB_NOTFOUND) {
        fprintf(stderr, "ERROR: some error iterating through db: %s \n",
            db_strerror(ret));
        db->err(db, ret, "ERROR: DB cursor");
    }

    if(cursorp != NULL)
      cursorp->close(cursorp);

}


void close_db(int signal) {
  fprintf(stderr, "WARNING: Caught signal, closing BDB database environment\n");
  if(db != NULL)
     bdb_close_env(db);
  if(f != NULL)
    fclose(f);
  exit(1);
}


int main(int argc, char** argv) {
                 
      if(argc !=3 && argc != 4) {
        fprintf(stderr, "ERROR: usage: <db-env> <db-name> [file-out] \n");
        exit(1);
      }

      register_for_signals(close_db);

      db = bdb_open_env(argv[1], g_db_env_flags, argv[2], g_db_flags | DB_RDONLY);
      if(db == NULL) {
          fprintf(stderr, "ERROR: bdb_open failed \n");
          exit(1);
      }

      if(argc == 4) 
        f = fopen(argv[3], "w");
      else 
        f = stdout; 

      loop_over();

      bdb_close_env(db);
      fclose(f);
      return 0;

}
