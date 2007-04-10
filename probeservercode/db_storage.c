#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "xmalloc.h"
#include "db_storage.h"

#define MIN_TIME_BETWEEN_PROBES (60 * 5)

//typedef struct sqlite3_stmt sqlite3_stmt;

// create the 'ssh_key_bindings' table if it does not already exist
void create_key_bindings_table(sqlite3 *db) {

	sqlite3_stmt *stmt1; 	
	const char* tail;
	char *zErrMsg = NULL;
	int rc;
	char *create_stmt1 = "CREATE TABLE IF NOT EXISTS" 
			" ssh_key_bindings "
			"(id INTEGER PRIMARY KEY AUTOINCREMENT, "
			"dns_name TEXT, key BLOB)";
  	rc = sqlite3_prepare_v2(db, create_stmt1, 
			strlen(create_stmt1), &stmt1, &tail);
  	rc = sqlite3_step(stmt1);
  	if( rc!=SQLITE_OK && rc != SQLITE_DONE){
    		DPRINTF(DEBUG_ERROR, "SQL error: %s\n", zErrMsg);
    		sqlite3_free(zErrMsg);
  	}
	
	sqlite3_finalize(stmt1);

}

// create the 'ssh_probes' table, if it does not already exist
void create_probes_table(sqlite3* db) {

	sqlite3_stmt *stmt1; 	
	const char* tail;
	char *zErrMsg = NULL;
	int rc;

	char *create_stmt2 = "CREATE TABLE IF NOT EXISTS" 
			" ssh_probes (id INTEGER, time INTEGER, ip_addr INTEGER)";
  	rc = sqlite3_prepare_v2(db, create_stmt2, 
			strlen(create_stmt2), &stmt1, &tail);
  	rc = sqlite3_step(stmt1);
  	if( rc!=SQLITE_OK && rc != SQLITE_DONE){
    		DPRINTF(DEBUG_ERROR, "SQL error: %s\n", zErrMsg);
    		sqlite3_free(zErrMsg);
  	}
	
	sqlite3_finalize(stmt1);
}


int get_last_probe_time(sqlite3* db, char* dns_name) {
	int rc;
	char *select_stmt1 = "SELECT id FROM ssh_key_bindings WHERE "
			"dns_name = ?";
	sqlite3_stmt *stmt1; 	
	const char* tail;

  	rc = sqlite3_prepare_v2(db, select_stmt1, 
			strlen(select_stmt1), &stmt1, &tail);
	
	rc = sqlite3_bind_text(stmt1, 1, dns_name, 
		strlen(dns_name), SQLITE_TRANSIENT);

	rc = sqlite3_step(stmt1);
	if(rc != SQLITE_ROW) {
		return -1;
	}

	int id = sqlite3_column_int(stmt1, 0);	
	sqlite3_finalize(stmt1);
	 
	char *select_stmt2 = "SELECT max(time) FROM ssh_probes "
			"where id = ?";

  	rc = sqlite3_prepare_v2(db, select_stmt2, 
			strlen(select_stmt2), &stmt1, &tail);
	rc = sqlite3_bind_int(stmt1, 1, id);

	rc = sqlite3_step(stmt1);
	if(rc != SQLITE_ROW) {
		return -1;
	}
	int time = sqlite3_column_int(stmt1, 0);
	return time;
}


// find the binding id stored in the database for a particular
// (dns-name, ip-address, key) trip.
// returns the associated ID or NO_BINDING
int get_binding_id(sqlite3* db, char* dns_name, char* blob, int blob_len) {
	int rc;
	char *select_stmt1 = "SELECT id FROM ssh_key_bindings WHERE "
			"dns_name = ? AND key = ?";
	sqlite3_stmt *stmt1; 	
	const char* tail;

  	rc = sqlite3_prepare_v2(db, select_stmt1, 
			strlen(select_stmt1), &stmt1, &tail);
	
	rc = sqlite3_bind_text(stmt1, 1, dns_name, 
		strlen(dns_name), SQLITE_TRANSIENT);
	rc = sqlite3_bind_blob(stmt1, 2, blob, 
			blob_len, SQLITE_TRANSIENT);

	rc = sqlite3_step(stmt1);
	if(rc != SQLITE_ROW) {
		return NO_BINDING;
	}

	int id = sqlite3_column_int(stmt1, 0);	
	sqlite3_finalize(stmt1);
	return id; 
}

void store_ssh_probe_result(sqlite3* db, char *dns_name, uint32_t ip_addr, 
				Key *key, int timestamp) {
	u_char* blob;
	int blob_size = 0;
	if(key == NULL){
		printf("no key to store \n");
		return;
	}
	printf("trying to convert key to blob \n");
	key_to_blob(key, &blob, &blob_size);
	int id = get_binding_id(db, dns_name, (char*)blob, blob_size);
	if(id == NO_BINDING) {
		// we've never seen this binding
		DPRINTF(DEBUG_DATABASE, "new binding for %s \n", dns_name);
		add_ssh_key_binding(db,dns_name,(char*)blob,blob_size);
		id = get_binding_id(db, dns_name, (char*)blob, blob_size);
		if(id == NO_BINDING) {
			DPRINTF(DEBUG_ERROR,	
			"No binding id after adding binding\n");
			return;
		}
		
	}
	add_ssh_probe(db, id, timestamp, ip_addr);
	xfree(blob);
}


// add an entry to the 'ssh_probes' table
void add_ssh_probe(sqlite3* db, int id, int timestamp, uint32_t ip_addr) {

	DPRINTF(DEBUG_DATABASE, "adding SSH probe for id = %d \n", id);
	char* add_stmt2 = "INSERT into ssh_probes values (?, ?, ?)";
	sqlite3_stmt *stmt2; 	
	const char *tail;
	int rc;
	char *zErrMsg = NULL;

  	rc = sqlite3_prepare_v2(db, add_stmt2, strlen(add_stmt2), 
			&stmt2, &tail);
	rc = sqlite3_bind_int(stmt2, 1, id);
	rc = sqlite3_bind_int(stmt2, 2, timestamp);
	rc = sqlite3_bind_int(stmt2, 3, ip_addr);
	rc = sqlite3_step(stmt2);
  	if( rc!=SQLITE_DONE ){
    		DPRINTF(DEBUG_ERROR,"SQL error (step): %s\n", zErrMsg);
    		sqlite3_free(zErrMsg);
  	}

	sqlite3_finalize(stmt2);
}

// add an entry to the 'ssh_key_bindings' table 
void add_ssh_key_binding(sqlite3* db, char *dns_name, char*blob, int blob_size) {

	char* add_stmt1 = "INSERT into ssh_key_bindings values (?, ?, ?)";
	sqlite3_stmt *stmt1; 	
	const char* tail;
	int rc;
	char *zErrMsg = NULL;

  	rc = sqlite3_prepare_v2(db, add_stmt1, strlen(add_stmt1), 
			&stmt1, &tail);
	rc = sqlite3_bind_text(stmt1, 2, dns_name, 
		strlen(dns_name), SQLITE_TRANSIENT);
	rc = sqlite3_bind_blob(stmt1, 3, blob, 
			blob_size, SQLITE_TRANSIENT);
	rc = sqlite3_step(stmt1);
  	if( rc!=SQLITE_DONE ){
    		DPRINTF(DEBUG_ERROR, "SQL error (step): %s\n", zErrMsg);
    		sqlite3_free(zErrMsg);
  	}
	sqlite3_finalize(stmt1);
}

// create a list of all 'time' values stored in the 'ssh_probes'
// table that have a particular id.  the 'results' parameter will
// point to an integer array after returning, which the caller must
// free.  The function returns the number of entries in results. 
int get_probes_for_binding(sqlite3* db, int binding_id, 
	int** timestamps, int** addresses) {

	int rc;
	sqlite3_stmt *stmt1; 	
	const char* tail;
	char *select_stmt1 = "SELECT count(*) FROM ssh_probes "
			"where id = ?";

  	rc = sqlite3_prepare_v2(db, select_stmt1, 
			strlen(select_stmt1), &stmt1, &tail);
	rc = sqlite3_bind_int(stmt1, 1, binding_id);

	rc = sqlite3_step(stmt1);
	if(rc != SQLITE_ROW) {
		DPRINTF(DEBUG_ERROR, 
			"Error, DB failed to return count(*) value\n");
		exit(1);
	}
	int total_count = sqlite3_column_int(stmt1,0);
	DPRINTF(DEBUG_MESSAGE, "we have %d total timestamps \n", total_count);
	*timestamps = (int*) malloc(sizeof(int) * total_count);
	*addresses = (int*) malloc(sizeof(int) * total_count);

	char *select_stmt2 = "SELECT time, ip_addr FROM ssh_probes "
			"where id = ? order by time";
	sqlite3_stmt *stmt2; 	

  	rc = sqlite3_prepare_v2(db, select_stmt2, 
			strlen(select_stmt2), &stmt2, &tail);
	rc = sqlite3_bind_int(stmt2, 1, binding_id);

	int i;
	for(i = 0; i < total_count; i++) {
		int rc = sqlite3_step(stmt2);
		if(rc != SQLITE_ROW){
			DPRINTF(DEBUG_ERROR, "Couldn't access expect row in"
				" 'ssh_probes'. quiting early. \n");
			return i; // only valid through i
		}
		int t = sqlite3_column_int(stmt2,0);
		int a = sqlite3_column_int(stmt2,1);
		(*timestamps)[i] = htonl(t);
		(*addresses)[i] = a;
	} 

	sqlite3_finalize(stmt1);
	sqlite3_finalize(stmt2);
	return total_count;
}

notary_header* build_packet(char* dns_name, uint16_t port, uint16_t key_type,
		int num_probes, int* timestamps, int* addresses, 
		char* blob, int blob_size) {

	int name_len = strlen(dns_name) + 1;
	int probes_len = sizeof(int) * num_probes;
	int headroom = sizeof(notary_header) + name_len;
	int total_len = headroom + sizeof(ssh_key_info) + 
			blob_size + (2 * probes_len);
	notary_header* hdr = (notary_header*) malloc(total_len);
        hdr->version = 1;
        hdr->msg_type = TYPE_FETCH_REPLY_FINAL;
        hdr->total_len = htons(total_len);
        hdr->name_len = htons(name_len);
        hdr->service_type = htons(key_type);
        hdr->service_port = htons(port);
	char* name_start = (char*)(hdr+1);
	memcpy(name_start, dns_name, name_len);

	ssh_key_info* info = (ssh_key_info*)(((char*)hdr) + headroom);
	info->key_len_bytes = htons((uint16_t)blob_size);
	info->num_probes = htons((uint16_t)num_probes);

	char *key_start = (char*)(info + 1);
	memcpy(key_start, blob, blob_size);
	char *probe_start = key_start + blob_size;
	memcpy(probe_start, timestamps, probes_len);
	probe_start += probes_len;
	memcpy(probe_start, addresses, probes_len);

	return hdr;
}



// returns a list of 'ssh_key_info' structs that represent 
// all information associated with the specified 'dns_name'
// all memory must be freed by the caller. 
ssh_msg_list* lookupName(sqlite3* db, char* dns_name, uint16_t port,
		uint16_t key_type) {

	char *zErrMsg = NULL;
	int rc;
	char *select_stmt1 = "SELECT id , key FROM ssh_key_bindings "
				"where dns_name = ?";
	sqlite3_stmt *stmt1; 	
	const char* tail;

	ssh_msg_list* head = (ssh_msg_list*)
			malloc(sizeof(ssh_msg_list));
	INIT_LIST_HEAD(&(head->list));

  	rc = sqlite3_prepare_v2(db, select_stmt1, 
			strlen(select_stmt1), &stmt1, &tail);
  	if( rc!=SQLITE_OK ){
    		DPRINTF(DEBUG_ERROR, "SQL error (prepare): %s\n", zErrMsg);
    		sqlite3_free(zErrMsg);
  	}

	rc = sqlite3_bind_text(stmt1, 1, dns_name, strlen(dns_name), 
				SQLITE_TRANSIENT);
  	if( rc!=SQLITE_OK ){
    		DPRINTF(DEBUG_ERROR, "SQL error (bind_text): %s\n", zErrMsg);
    		sqlite3_free(zErrMsg);
  	}

	DPRINTF(DEBUG_DATABASE, "DB look-up for dns-name = %s \n", dns_name);
	while((rc = sqlite3_step(stmt1) == SQLITE_ROW)) {
		int id = sqlite3_column_int(stmt1,0);

		DPRINTF(DEBUG_DATABASE, "Found id = %d \n", id);
		int *timestamps, *addresses; 
		int blob_size = sqlite3_column_bytes(stmt1,1);
		char *blob = (char*)sqlite3_column_blob(stmt1,1);

		int num_probes = get_probes_for_binding(db, id, &timestamps, &addresses);
		notary_header* hdr = build_packet(dns_name, port, key_type, 
			num_probes,timestamps, addresses, blob, blob_size);

		free(timestamps);
		free(addresses);

		ssh_msg_list* elem = (ssh_msg_list*)
				malloc(sizeof(ssh_msg_list));
		elem->hdr = hdr;

		list_add(&(elem->list),&(head->list));
		
	} // end ROW for-loop

	if( rc != SQLITE_OK && rc != SQLITE_DONE ){
    		fprintf(stderr, "SQL error (step): %s\n", zErrMsg);
    		sqlite3_free(zErrMsg);
  	}

	sqlite3_finalize(stmt1);
	return head;
}


// initialize a sqlite database with filename 'fname'
// will create the 'ssh_key_bindings' and 'ssh_probes' 
// tables if they do not already exist
sqlite3* db_init(char *fname) {

	sqlite3 *db;
	int rc;
	rc = sqlite3_open(fname, &db);
  	if( rc ){
    		fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
    		sqlite3_close(db);
    		exit(1);
  	}	

	create_key_bindings_table(db);
	create_probes_table(db);
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

