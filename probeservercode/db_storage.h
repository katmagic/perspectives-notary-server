#ifndef _DB_STORAGE_H_
#define _DB_STORAGE_H_

#include "../common.h"
#include "probe_server.h"
#include <sqlite3.h>


#define NO_SERVICE -1
#define NO_KEY -2

void store_ssh_probe_result(sqlite3* db, char *dns_name, uint16_t port,
	uint32_t ip_addr, Key *key, int timestamp) ;

int get_last_obs_time(sqlite3* db, char* dns_name, uint16_t port,
	uint16_t type);

void insert_observation(sqlite3* db, int sid, int kid, 
		int timestamp, uint32_t ip_addr);

int get_probes_for_binding(sqlite3* db, int binding_id, 
	int** timestamps, int** addresses);

ssh_result_list* get_all_observations(sqlite3* db,
                char* dns_name, uint16_t port, uint16_t key_type);

sqlite3* db_init(char *fname) ;
void db_close(sqlite3* db);

int get_service_id(sqlite3* db, char* dns_name, uint16_t port);
int get_key_id(sqlite3* db, char* blob, int blob_len, int key_type);


#endif
