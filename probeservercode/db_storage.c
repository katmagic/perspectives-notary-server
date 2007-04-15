#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "xmalloc.h"
#include "db_storage.h"
#include "../util/key_util.h"

// create the 'ssh_key_bindings' table if it does not already exist
void create_table(char* create_stmt, sqlite3 *db) {

	sqlite3_stmt *stmt; 	
	const char* tail;
	char *zErrMsg = NULL;
	int rc;
  	rc = sqlite3_prepare_v2(db, create_stmt, 
			strlen(create_stmt), &stmt, &tail);
  	rc = sqlite3_step(stmt);
  	if( rc!=SQLITE_OK && rc != SQLITE_DONE){
    		DPRINTF(DEBUG_ERROR, "SQL error: %s\n", zErrMsg);
    		sqlite3_free(zErrMsg);
  	}
	
	sqlite3_finalize(stmt);

}

void create_all_tables(sqlite3* db) {

	char *create_service_id = "CREATE TABLE IF NOT EXISTS service_id "
			"(sid INTEGER PRIMARY KEY AUTOINCREMENT, "
			"dns_name TEXT, port INTEGER)";
	create_table(create_service_id, db);

	char *create_key_id = "CREATE TABLE IF NOT EXISTS key_id "
			"(kid INTEGER PRIMARY KEY AUTOINCREMENT, "
			" key BLOB, type INTEGER)";
	create_table(create_key_id, db);

	char *create_observations = "CREATE TABLE IF NOT EXISTS" 
			" observations (sid INTEGER, kid INTEGER," 
			" time INTEGER, ip_addr INTEGER)";
	create_table(create_observations, db);

	char *create_background_probes = "CREATE TABLE IF NOT EXISTS" 
			" background_probes (sid INTEGER, "
			" next_probe INTEGER, wait INTEGER, " 
			" failures INTEGER)";
	create_table(create_background_probes, db);
}	


int get_last_obs_time(sqlite3* db, char* dns_name, uint16_t port,
		uint16_t type) {
	int rc;
	sqlite3_stmt *stmt; 	
	const char* tail;

	int sid = get_service_id(db, dns_name, port);
	if(sid == NO_SERVICE) 
		return NO_SERVICE;	 

	char *select_stmt2 = "SELECT max(time) FROM key_id,observations "
			"where sid = ? and key_id.kid = observations.kid "
			" and type = ?";

  	rc = sqlite3_prepare_v2(db, select_stmt2, 
			strlen(select_stmt2), &stmt, &tail);
	rc = sqlite3_bind_int(stmt, 1, sid);
	rc = sqlite3_bind_int(stmt, 2, type);

	rc = sqlite3_step(stmt);
	if(rc != SQLITE_ROW) {
		return NO_KEY;
	}
	int time = sqlite3_column_int(stmt, 0);
	sqlite3_finalize(stmt);
	return time;
}


int get_service_id(sqlite3* db, char* dns_name, uint16_t port) {

	int rc;
	char *select = "SELECT sid from service_id WHERE "
			"dns_name = ? and port = ?";

	sqlite3_stmt *stmt; 	
	const char* tail;
  	rc = sqlite3_prepare_v2(db, select, 
			strlen(select), &stmt, &tail);
	rc = sqlite3_bind_text(stmt, 1, dns_name, 
		strlen(dns_name), SQLITE_TRANSIENT);
	rc = sqlite3_bind_int(stmt,2, port);	

	rc = sqlite3_step(stmt);
	if(rc != SQLITE_ROW) {
		sqlite3_finalize(stmt);
		return NO_SERVICE;
	}

	int sid = sqlite3_column_int(stmt, 0);	
	sqlite3_finalize(stmt);
	return sid;
}

int get_key_id(sqlite3* db, char* blob, int blob_len, int key_type) {
	int rc;
	char *select_stmt1 = "SELECT kid FROM key_id WHERE key = ? "
			" and type = ?";
	sqlite3_stmt *stmt1; 	
	const char* tail;

  	rc = sqlite3_prepare_v2(db, select_stmt1, 
			strlen(select_stmt1), &stmt1, &tail);
	rc = sqlite3_bind_blob(stmt1, 1, blob, 
			blob_len, SQLITE_TRANSIENT);
	rc = sqlite3_bind_int(stmt1,2, key_type);

	rc = sqlite3_step(stmt1);
	if(rc != SQLITE_ROW) {
		sqlite3_finalize(stmt1);
		return NO_KEY; 
	}

	int kid = sqlite3_column_int(stmt1, 0);	
	sqlite3_finalize(stmt1);
	return kid; 
}

Key *get_key(sqlite3 *db, int kid) {

	int rc;
	char *select_stmt1 = "SELECT key, type FROM key_id WHERE kid = ?";
	sqlite3_stmt *stmt1; 	
	const char* tail;

  	rc = sqlite3_prepare_v2(db, select_stmt1, 
			strlen(select_stmt1), &stmt1, &tail);
	rc = sqlite3_bind_int(stmt1, 1, kid);
	rc = sqlite3_step(stmt1);
	if(rc != SQLITE_ROW) {
		sqlite3_finalize(stmt1);
		return NULL; 
	}

	int buf_size = sqlite3_column_bytes(stmt1,0);
	if(buf_size <= 0) {
		DPRINTF(DEBUG_ERROR, "Error reading key from key_id table \n");
		return NULL;
	}
	char* buf = (char*) sqlite3_column_blob(stmt1,0);
	int key_type = sqlite3_column_int(stmt1, 1);
	Key *key = buf_to_key(buf, buf_size, key_type);

	sqlite3_finalize(stmt1);
	return key;
}

// add a new entry to the service_id table 
void add_new_service(sqlite3* db, char *dns_name, uint16_t port) {

	char* add_stmt1 = "INSERT into service_id values (?, ?, ?)";
	sqlite3_stmt *stmt1; 	
	const char* tail;
	int rc;
	char *zErrMsg = NULL;

	printf("inserting new service %s : %d \n", dns_name, port);
  	rc = sqlite3_prepare_v2(db, add_stmt1, strlen(add_stmt1), 
			&stmt1, &tail);
	rc = sqlite3_bind_text(stmt1, 2, dns_name, 
		strlen(dns_name), SQLITE_TRANSIENT);
	rc = sqlite3_bind_int(stmt1, 3, port);

	rc = sqlite3_step(stmt1);
  	if( rc!=SQLITE_DONE ){
    		DPRINTF(DEBUG_ERROR, "SQL error (step): %s\n", zErrMsg);
    		sqlite3_free(zErrMsg);
  	}
	sqlite3_finalize(stmt1);
}

void add_new_key(sqlite3* db, char*blob, int blob_size, int key_type) {
	char* add_stmt1 = "INSERT into key_id values (?, ?, ?)";
	sqlite3_stmt *stmt1; 	
	const char* tail;
	int rc;
	char *zErrMsg = NULL;

  	rc = sqlite3_prepare_v2(db, add_stmt1, strlen(add_stmt1), 
			&stmt1, &tail);

	rc = sqlite3_bind_blob(stmt1, 2, blob, 
			blob_size, SQLITE_TRANSIENT);
	rc = sqlite3_bind_int(stmt1, 3, key_type);
	rc = sqlite3_step(stmt1);
  	if( rc!=SQLITE_DONE ){
    		DPRINTF(DEBUG_ERROR, "SQL error (step): %s\n", zErrMsg);
    		sqlite3_free(zErrMsg);
  	}
	sqlite3_finalize(stmt1);
}

		// TODO: fix join code so only correct key type is returned
		// TODO: add periodic probing
void store_ssh_probe_result(sqlite3* db, char *dns_name, uint16_t port,
				uint32_t ip_addr, 
				Key *key, int timestamp) {
	if(key == NULL){
		printf("no key to store \n");
		return;
	}

	char* buf;
	int buf_size = 0;
	key_to_buf(key, &buf, &buf_size);

	int kid = get_key_id(db, buf, buf_size, key->type);
	if(kid == NO_KEY) {
		// we've never seen this key before
		DPRINTF(DEBUG_DATABASE, "New key id for %s\n", dns_name);
		add_new_key(db, buf, buf_size, key->type);
		kid = get_key_id(db, buf, buf_size, key->type);
		if(kid == NO_KEY) {
			DPRINTF(DEBUG_ERROR, "Error adding key ID \n");
			return;
		}
		
	}

	int sid = get_service_id(db, dns_name, port);
	if(sid == NO_SERVICE) {
		// we've never seen this service before
		DPRINTF(DEBUG_DATABASE, "New service id for %s: %d\n", 
				dns_name, port);
		add_new_service(db, dns_name, port);
		sid = get_service_id(db, dns_name, port);
		if(sid == NO_SERVICE) {
			DPRINTF(DEBUG_ERROR, "Error adding service ID \n");
			return;
		}
		
	}

	insert_observation(db, sid, kid, timestamp, ip_addr);
	xfree(buf);
}


// add an entry to the 'observations' table
void insert_observation(sqlite3* db, int sid, int kid,  
	int timestamp, uint32_t ip_addr) {

	DPRINTF(DEBUG_DATABASE, "adding observation for sid = %d "
			" kid = %d\n", sid, kid);
	char* add_stmt2 = "INSERT into observations values (?, ?, ?, ?)";
	sqlite3_stmt *stmt2; 	
	const char *tail;
	int rc;
	char *zErrMsg = NULL;

  	rc = sqlite3_prepare_v2(db, add_stmt2, strlen(add_stmt2), 
			&stmt2, &tail);
	rc = sqlite3_bind_int(stmt2, 1, sid);
	rc = sqlite3_bind_int(stmt2, 2, kid);
	rc = sqlite3_bind_int(stmt2, 3, timestamp);
	rc = sqlite3_bind_int(stmt2, 4, ip_addr);
	rc = sqlite3_step(stmt2);
  	if( rc!=SQLITE_DONE ){
    		DPRINTF(DEBUG_ERROR,"SQL error (step): %s\n", zErrMsg);
    		sqlite3_free(zErrMsg);
  	}

	sqlite3_finalize(stmt2);
}

// results a ssh_result_list with all observations
// for this key-id
ssh_result_list *get_observations_for_key(sqlite3* db, int kid) {
		
	Key *key = get_key(db, kid);
	if(key == NULL) {
		DPRINTF(DEBUG_ERROR, "Unable to access kid = %d "
			" from DB \n", kid);
		return NULL;
	}
	ssh_result_list* result = (ssh_result_list*)
				malloc(sizeof(ssh_result_list));
	result->key = key;

	int rc;
	sqlite3_stmt *stmt1; 	
	const char* tail;
	char *select_stmt1 = "SELECT count(*) FROM observations "
			"where kid = ?";

  	rc = sqlite3_prepare_v2(db, select_stmt1, 
			strlen(select_stmt1), &stmt1, &tail);
	rc = sqlite3_bind_int(stmt1, 1, kid);

	rc = sqlite3_step(stmt1);
	if(rc != SQLITE_ROW) {
		DPRINTF(DEBUG_ERROR, 
			"Error, DB failed to return count(*) value\n");
		return NULL;
	}
	int total_count = sqlite3_column_int(stmt1,0);
	DPRINTF(DEBUG_MESSAGE, "we have %d total timestamps \n", 
				total_count);

	result->num_probes = total_count;
	result->timestamps = (int*) malloc(sizeof(int) * total_count);
	result->addresses = (int*) malloc(sizeof(int) * total_count);

	char *select_stmt2 = "SELECT time, ip_addr FROM observations "
			"where kid = ? order by time";
	sqlite3_stmt *stmt2; 	

  	rc = sqlite3_prepare_v2(db, select_stmt2, 
			strlen(select_stmt2), &stmt2, &tail);
	rc = sqlite3_bind_int(stmt2, 1, kid);

	int i;
	for(i = 0; i < total_count; i++) {
		int rc = sqlite3_step(stmt2);
		if(rc != SQLITE_ROW){
			DPRINTF(DEBUG_ERROR, "Couldn't access expect row in"
				" 'ssh_probes'. quiting early. \n");
			result->num_probes = i; // only valid through i
			return result;
		}
		int t = sqlite3_column_int(stmt2,0);
		int a = sqlite3_column_int(stmt2,1);
		result->timestamps[i] = htonl(t);
		result->addresses[i] = a;
	} 

	sqlite3_finalize(stmt1);
	sqlite3_finalize(stmt2);
	return result;
}


// returns a list of 'ssh_result_list' structs that represent 
// all key observations associated with the specified 'dns_name/port'
// the caller must remember to free the memory allocated for list
// elements
ssh_result_list* get_all_observations(sqlite3* db, 
		char* dns_name, uint16_t port, uint16_t key_type) {

	char *zErrMsg = NULL;
	int rc;
	char *select_stmt1 = "SELECT DISTINCT kid FROM "
		"observations where sid = ? ";
	sqlite3_stmt *stmt1; 	
	const char* tail;
	
	ssh_result_list* head = (ssh_result_list*)
		malloc(sizeof(ssh_result_list));
			
	INIT_LIST_HEAD(&(head->list));

	DPRINTF(DEBUG_DATABASE, "DB look-up for dns-name = %s  "
		" with key-type = %d \n", dns_name, key_type);
	int sid = get_service_id(db, dns_name, port);
	if(sid == NO_SERVICE){
		DPRINTF(DEBUG_ERROR, "Found no service for %s : %d \n", 
			dns_name, port);
		return NULL;
	}

  	rc = sqlite3_prepare_v2(db, select_stmt1, 
			strlen(select_stmt1), &stmt1, &tail);
	rc = sqlite3_bind_int(stmt1, 1, sid);
	rc = sqlite3_bind_int(stmt1, 2, key_type);

	// loop once for each unique key that we have seen for this
	// service identifier
	int num_keys = 0; 
	while((rc = sqlite3_step(stmt1) == SQLITE_ROW)) {
		num_keys++;
		int kid = sqlite3_column_int(stmt1,0);

		ssh_result_list *result = 
			get_observations_for_key(db, kid);

		list_add(&(result->list),&(head->list));
		
	} // end ROW for-loop
	DPRINTF(DEBUG_INFO, "Found total of %d keys \n", num_keys);

	if( rc != SQLITE_OK && rc != SQLITE_DONE ){
    		fprintf(stderr, "SQL error (step): %s\n", zErrMsg);
    		sqlite3_free(zErrMsg);
  	}

	sqlite3_finalize(stmt1);
	return head;
}


// initialize a sqlite database with filename 'fname'
// will create all tables if they do not already exist
sqlite3* db_init(char *fname) {

	sqlite3 *db;
	int rc;
	rc = sqlite3_open(fname, &db);
  	if( rc ){
    		fprintf(stderr, "Can't open database: %s\n", 
			sqlite3_errmsg(db));
    		sqlite3_close(db);
    		exit(1);
  	}	
	create_all_tables(db);
	return db;
}

// closes the database file 
void db_close(sqlite3* db) {
  sqlite3_close(db);
}

/*
int main(int argc, char** argv) {

	if(argc != 2) {
		fprintf(stderr, "usage: db_util <database name>\n");
		return 1;
	}

	sqlite3* db = db_init(argv[1]);	

	db_close(db);

  	return 0;
}
*/

