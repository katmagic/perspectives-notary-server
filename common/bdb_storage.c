
#include <stdlib.h>
#include <string.h>

#include "db.h"
#include "notary_util.h"
#include "notary_crypto.h"

DB * bdb_open(char *filename, uint32_t open_flags) {
      DB *dbp;
      int ret;
      
      if ((ret = db_create(&dbp, NULL, 0)) != 0) {
            fprintf(stderr, "db_create: %s\n", db_strerror(ret));
            printf("error on create() \n");
            exit (1);
      }
      if ((ret = dbp->open(dbp,NULL, filename, NULL, 
                    DB_HASH, open_flags, 0664)) != 0) {
            dbp->err(dbp, ret, "%s", filename);
            fprintf(stderr, "open: %s\n", db_strerror(ret));
            printf("error on open() \n");
            exit(1);
      }
      return dbp;
}

DB * bdb_open_env(char *env_file, uint32_t env_flags, 
                  char *db_name, uint32_t db_open_flags) {
      DB_ENV *dbenv;
     
      int ret;
      ret = db_env_create(&dbenv, 0);
      if(ret) {
        printf("db_evn_create failed: %s \n", db_strerror(ret));
        exit(1);
      }

      ret = dbenv->open(dbenv, env_file, env_flags, 0);
      if(ret) {
        printf("dbenv->open failed: %s \n", db_strerror(ret));
        exit(1);
      }

      DB *dbp;
      
      if ((ret = db_create(&dbp, dbenv, 0)) != 0) {
            fprintf(stderr, "db_create: %s\n", db_strerror(ret));
            exit (1);
      }
      if ((ret = dbp->open(dbp,NULL, db_name, NULL, 
                    DB_HASH, db_open_flags, 0)) != 0) {
            dbp->err(dbp, ret, "%s", db_name);
            exit(1);
      }
      return dbp;
}

void bdb_close(DB *db){
  db->close(db,0);
}


void bdb_close_env(DB *db){
  DB_ENV *env = db->get_env(db);
  db->close(db,0);
  
  if(env)
    env->close(env,0);

}

unsigned int get_data(DB* db, char* service_id, char* buf,
                            int max_size, uint32_t flags) {
            DBT key,data;
            int ret;
            memset(&key, 0, sizeof(key));
            memset(&data, 0, sizeof(data));
            key.data = service_id;
            key.size = strlen(service_id) + 1;
            key.flags = flags; // docs say this is needed 
            data.flags = flags; 
 
            if ((ret = db->get(db, NULL, &key, &data, 0)) != 0){
                if(ret == DB_NOTFOUND) {
              //    DPRINTF(DEBUG_INFO, "No service-entry for: '%s' (len = %d ) \n",
                //      (char*)key.data, key.size);
                }else {
                  db->err(db, ret, "DB->get");
                }
                return -1;
            }
            if(data.size > max_size) {
                DPRINTF(DEBUG_ERROR, 
                    "data for '%s' is too big for buffer in get_data\n",
                    service_id);
                return -1;
            }
            memcpy(buf, data.data, data.size); 
	    
	    if(flags & DB_DBT_MALLOC || flags & DB_DBT_USERMEM)
	    	free(data.data);     
            return data.size;
}

int store_data(DB *db, char *host_and_port, char *buf, 
                            unsigned int buf_len) {
            DBT key,data;
            int ret;

            memset(&key, 0, sizeof(key));
            memset(&data, 0, sizeof(data));

            key.data = host_and_port;
            key.size = strlen(host_and_port) + 1;
            data.data = buf;
            data.size = buf_len;

            if ((ret = db->put(db, NULL, &key, &data, 0)) != 0){
                db->err(db, ret, "DB->put");
                return ret;
            }
            return 0;
}


void delete_record(DB * db, char *record_id) {
  DBT key; 

  memset(&key, 0, sizeof(DBT));
  key.data = record_id;
  key.size = strlen(record_id) + 1; 

  db->del(db, NULL, &key,0); 

}

// just touch all the data so it will be in memory for sure
void warm_db(DB* db) {
    DBC *cursorp;
    DBT key,data;
    int ret; 


    printf("begin warming \n");
    int count = 0;
    ret = db->cursor(db, NULL, &cursorp,0);
    if(ret) {
        printf("error opening cursor\n");
        db->err(db, ret, "Cursor open: ");
        exit(1);
    }
    memset(&key, 0, sizeof(key));
    memset(&data, 0, sizeof(data));
    while((ret = cursorp->get(cursorp,&key,&data, DB_NEXT)) == 0) {
        char a = ((char*)key.data)[0];
        char b = ((char*)data.data)[0];
        b = a; // just shut the compiler up
        a = b;
     //   printf("key: %s \n", (char*)key.data);
        ++count;
    }
    printf("done warming %d entries \n", count);

    if(ret != DB_NOTFOUND) {
        printf("some error warming the cache: %s \n",
            db_strerror(ret));
        db->err(db, ret, "DB warming ");
    }

    if(cursorp != NULL)
      cursorp->close(cursorp);
}

void record_observation(DB* db, RSA *priv_key,
                                  char* service_id, char *digest, 
                                  int digest_len,
                                  int key_type, int timestamp,
                                  BOOL do_signature) {
      char buf[MAX_PACKET_LEN];
      ssh_key_info_list *info_list = NULL;

      unsigned int data_len = get_data(db, service_id ,buf, 
                                         MAX_PACKET_LEN,0);
      if(data_len != -1) 
        info_list = list_from_data(buf, data_len,SIGNATURE_LEN);
      
      if(info_list == NULL) {
          // allocate new list-head
          DPRINTF(DEBUG_INFO, "Creating new DB entry for: %s \n", service_id); 
          info_list = (ssh_key_info_list*)malloc(sizeof(ssh_key_info_list));
          INIT_LIST_HEAD(&(info_list->list));
      }
      assert(info_list);

      //printf("BEFORE: \n");
      //print_key_info_list(info_list);
      //printf("******************* \n");

      add_observation_to_list(info_list, digest,digest_len, key_type,
                                        timestamp);

      //printf("AFTER: \n");
      //print_key_info_list(info_list);
      // create signature and store
      int name_len = strlen(service_id) + 1;
      memcpy(buf, service_id, name_len);

      while(1) { 
      	data_len = data_from_list(info_list, buf + name_len, 
                                      MAX_PACKET_LEN - name_len);
	if(data_len < 0) return;
  
	if(data_len < MAX_SERVICE_ENTRY_LEN) 
	   break; 
       	prune_oldest_timestamp(info_list, timestamp); 
      }

      unsigned char sig_buf[SIGNATURE_LEN];

      unsigned int sig_len = SIGNATURE_LEN;
      int ret; 

      if(do_signature) {
        sig_len = -1; 
        ret = get_signature(buf, name_len + data_len, priv_key,
                                  sig_buf, &sig_len);
        if(ret) {
          DPRINTF(DEBUG_ERROR,
              "error calculating signature for: %s \n", service_id);
          return;
        }
        assert(SIGNATURE_LEN == sig_len);
      }

      if((sig_len + name_len + data_len) > MAX_PACKET_LEN){
          DPRINTF(DEBUG_ERROR,"Max record size cannot fit signature\n");
          return;
      }
      char *data_end = ((char*)buf) + name_len + data_len;
      memcpy(data_end , sig_buf, sig_len);
      // we don't store the service-name as data, since it is the key
      ret = store_data(db, service_id, buf + name_len, 
                                      data_len + sig_len); 
      if(ret) 
        DPRINTF(DEBUG_ERROR, "error storing data \n");

      free_key_info_list(info_list);
}


