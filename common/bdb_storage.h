#ifndef _BDB_STORAGE_H_
#define _BDB_STORAGE_H_

#include "db.h"
#include <openssl/rsa.h>
#include "common.h"

DB * bdb_open(char *filename, uint32_t open_flags);
DB * bdb_open_env(char *evn_file, uint32_t evn_flags, 
                  char *db_name, uint32_t db_open_flags);

void bdb_close(DB *db);
void bdb_close_env(DB *db);

unsigned int get_data(DB* db, char* host_and_port, char* buf,
                            int max_size, uint32_t flags);


int store_data(DB *db, char *host_and_port, char *buf, 
                            unsigned int buf_len);

void warm_db(DB* db);

void record_observation(DB* db, RSA *priv_key,
                                  char* service_id, char *digest, 
                                  int digest_len,
                                  int key_type, int timestamp,
                                  BOOL do_signature);


#endif

