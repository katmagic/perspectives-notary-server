#ifndef _DB_STORAGE_H_
#define _DB_STORAGE_H_

#include "../common.h"
#include "probe_server.h"
#include <sqlite3.h>


#define NO_BINDING -1

void create_key_bindings_table(sqlite3 *db);
void create_probes_table(sqlite3* db) ;
int get_binding_id(sqlite3* db, char* dns_name, char* blob, int blob_len) ;
void store_ssh_probe_result(sqlite3* db, char *dns_name, uint32_t ip_addr,
                                Key *key, int timestamp) ;

int get_last_probe_time(sqlite3* db, char* dns_name);
void add_ssh_probe(sqlite3* db, int id, int timestamp, uint32_t ip_addr);
void add_ssh_key_binding(sqlite3* db, char *dns_name, char*blob, int blob_size);
int get_probes_for_binding(sqlite3* db, int binding_id, 
	int** timestamps, int** addresses);

ssh_msg_list* lookupName(sqlite3* db, char* dns_name, uint16_t port,
		uint16_t key_type);

sqlite3* db_init(char *fname) ;
void db_close(sqlite3* db);


#endif
