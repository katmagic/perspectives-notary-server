

#include "common.h"
#include "bdb_storage.h"


#define ENV_LOCATION "/home/danwent/db_test"
#define DB_NAME "test.db"

void db_test_reader() {
  
  uint32_t env_flags = DB_CREATE | DB_INIT_MPOOL | DB_INIT_CDB;
  uint32_t db_flags = DB_RDONLY;
  DB *db = bdb_open_env(ENV_LOCATION, env_flags, 
                          DB_NAME, db_flags); 
  while(1) {
    DBT key,data;
    int ret;
    memset(&key, 0, sizeof(key));
    memset(&data, 0, sizeof(data));

    int i;
    for(i = 0; i < 20; i++) { 
      key.data = &i;
      key.size = sizeof(int);

      if ((ret = db->get(db, NULL, &key, &data, 0)) != 0){
        if(ret == DB_NOTFOUND) {
          printf("No data found for key : '%d' \n", i);
        } else {
          db->err(db, ret, "DB->get");
        }
      }else {
        printf("%d = %d \n", i, *(int*)data.data);
      }
    }
    sleep(1);
  }

  bdb_close_env(db);
}

void db_test_writer() {
  uint32_t env_flags = DB_CREATE | DB_INIT_MPOOL | DB_INIT_CDB;
  uint32_t db_flags = DB_CREATE;
  DB *db = bdb_open_env(ENV_LOCATION, env_flags, 
                          DB_NAME, db_flags); 

  DBT key,data;
  int ret;

  memset(&key, 0, sizeof(key));
  memset(&data, 0, sizeof(data));

  int i;
  for(i = 0; i < 20; i++) {
    key.data = &i;
    key.size = sizeof(int);
    data.size = sizeof(int);

     if ((ret = db->get(db, NULL, &key, &data, 0)) != 0){
        if(ret == DB_NOTFOUND) {
          printf("No data found for key : '%d' \n", i);
        } else {
          db->err(db, ret, "DB->get");
        }
        continue;
      }
    int value = *(int*)data.data;
    ++value;
    data.data = &value;

    if((ret = db->put(db, NULL, &key, &data,0)) != 0) {
      db->err(db, ret, "DB->put");
    }
  }

  printf("done writing \n");
  bdb_close_env(db);
}

unsigned int notary_debug = DEBUG_ERROR;

int main(int argc, char** argv) {

  if(argc != 2) {
    printf("usage: <r | w> \n");
    exit(1);
  }

  if(argv[1][0] == 'r')
    db_test_reader();
  else if(argv[1][0] == 'w') 
    db_test_writer();
  else
    printf("invalid value: must be 'r' or 'w'\n");

}
