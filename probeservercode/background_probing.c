#include "../common.h"
#include "background_probing.h"
#include "ssh-keyscan.h"
#include "db_storage.h"

void bg_get_probe_info(sqlite3 *db, int sid, bg_probe_info *info) {

	int rc;
	char *select = "SELECT next_probe, wait, last_success from background_probes WHERE sid = ? ";

	sqlite3_stmt *stmt; 	
	const char* tail;
  	rc = sqlite3_prepare_v2(db, select, 
			strlen(select), &stmt, &tail);
	rc = sqlite3_bind_int(stmt, 1 , sid);	
	rc = sqlite3_step(stmt);
	if(rc != SQLITE_ROW){
		info->sid = NO_SERVICE;
		sqlite3_finalize(stmt);
		return;
	}

	info->sid = sid;
	info->next_probe = sqlite3_column_int(stmt,0);
	info->wait = sqlite3_column_int(stmt,1);
	info->last_success = sqlite3_column_int(stmt,2);

	sqlite3_finalize(stmt);
}


void bg_remove_probe_info(sqlite3 *db, int sid) {

	int rc;
	char *select = "DELETE from background_probes WHERE sid = ? ";

	sqlite3_stmt *stmt; 	
	const char* tail;
  	rc = sqlite3_prepare_v2(db, select, 
			strlen(select), &stmt, &tail);
	rc = sqlite3_bind_int(stmt, 1 , sid);	
	rc = sqlite3_step(stmt);
	if(rc != SQLITE_DONE) {
		DPRINTF(DEBUG_ERROR, "error while removing bg-probe "
		"entry for sid = %d \n", sid);
	}

	sqlite3_finalize(stmt);
}


// checks whether this service-id is already in
// the background probing table
BOOL bg_already_in_table(sqlite3 *db, int sid) {
	bg_probe_info info;
	bg_get_probe_info(db,sid,&info);
	return (info.sid != NO_SERVICE);
}



int get_most_recent_keytype(sqlite3* db, int sid) {
	int rc;
	sqlite3_stmt *stmt; 	
	const char* tail;

	char *select_stmt2 = "SELECT kid FROM observations where sid = ? ORDER BY time DESC";

  	rc = sqlite3_prepare_v2(db, select_stmt2, 
			strlen(select_stmt2), &stmt, &tail);
	rc = sqlite3_bind_int(stmt, 1, sid);

	rc = sqlite3_step(stmt);
	if(rc != SQLITE_ROW) {
		return NO_KEY;
	}
	int kid = sqlite3_column_int(stmt, 0);
	sqlite3_finalize(stmt);
	Key* key = get_key(db, kid);
	if(key == NULL) return NO_KEY;
	return key->type;
}




void bg_update_entry(sqlite3* db, bg_probe_info *info) {

	char* add_stmt1 = "UPDATE background_probes set next_probe = ?, "
			" wait = ?, last_success = ? where sid = ?";
	sqlite3_stmt *stmt1; 	
	const char* tail;
	int rc;
	char *zErrMsg = NULL;

  	rc = sqlite3_prepare_v2(db, add_stmt1, strlen(add_stmt1), 
			&stmt1, &tail);
	rc = sqlite3_bind_int(stmt1, 1, info->next_probe);
	rc = sqlite3_bind_int(stmt1, 2, info->wait);
	rc = sqlite3_bind_int(stmt1, 3, info->last_success);
	rc = sqlite3_bind_int(stmt1, 4, info->sid);

	rc = sqlite3_step(stmt1);
  	if( rc!=SQLITE_DONE ){
    		DPRINTF(DEBUG_ERROR, "SQL error (step): %s\n", zErrMsg);
    		sqlite3_free(zErrMsg);
  	}
	sqlite3_finalize(stmt1);
}

void bg_add_new_service(sqlite3 *db, int sid) {

	char* add_stmt1 = "INSERT into background_probes values (?, ?, ?, ?)";
	sqlite3_stmt *stmt1; 	
	const char* tail;
	int rc;
	char *zErrMsg = NULL;

	DPRINTF(DEBUG_INFO, "Adding BG-service for sid = %d \n", sid);
	struct timeval now;
	gettimeofday(&now, NULL);
	int next = now.tv_sec + BG_PROBE_INTERVAL;

  	rc = sqlite3_prepare_v2(db, add_stmt1, strlen(add_stmt1), 
			&stmt1, &tail);
	rc = sqlite3_bind_int(stmt1, 1, sid);
	rc = sqlite3_bind_int(stmt1, 2, next);
	rc = sqlite3_bind_int(stmt1, 3, BG_PROBE_INTERVAL);
	rc = sqlite3_bind_int(stmt1, 4, (int)now.tv_sec);

	rc = sqlite3_step(stmt1);
  	if( rc!=SQLITE_DONE ){
    		DPRINTF(DEBUG_ERROR, "SQL error (step): %s\n", zErrMsg);
    		sqlite3_free(zErrMsg);
  	}
	sqlite3_finalize(stmt1);

}

void bg_run_single_probe(sqlite3* db, int sid) {
	char *host;
	uint16_t port;

	// do this background probe for the most recent
	// type of key that was queried before.  In the 
	// future, we may want to query for all key-types
	int key_type = get_most_recent_keytype(db, sid);
	
	if(key_type == NO_KEY) 
		key_type = KEY_RSA;
	DPRINTF(DEBUG_INFO, "Background probe for sid = %d with key type = %d \n", sid, key_type);

	if(NO_SERVICE == get_service_info(db, sid, &host, &port)) {
		DPRINTF(DEBUG_ERROR, "Failed to get service info for %d \n", sid);
		return;
	}

	// hand this off to probing layer
	do_single_probe(host, key_type, port, NULL);
}


void bg_run_periodic_probes(sqlite3 *db, int cur_time){

	struct timeval now;
	gettimeofday(&now, NULL);

	int rc;
	char *select = "SELECT sid from background_probes "
		" WHERE next_probe < ?";

	sqlite3_stmt *stmt; 	
	const char* tail;
  	rc = sqlite3_prepare_v2(db, select, 
			strlen(select), &stmt, &tail);
	rc = sqlite3_bind_int(stmt, 1 , now.tv_sec);	

	while(TRUE) {
		int rc = sqlite3_step(stmt);
		if(rc != SQLITE_ROW){
			break;
		}
		int sid = sqlite3_column_int(stmt,0);
		bg_run_single_probe(db, sid);
	} 

	sqlite3_finalize(stmt);
}

void bg_probe_result(sqlite3* db, char* dns_name, uint16_t port,  BOOL succeeded) {

	struct timeval now;
	gettimeofday(&now,NULL);
	int time = (int) now.tv_sec;

	// get sid
	int sid = get_service_id(db, dns_name, port);
	if(sid == NO_SERVICE) {
		DPRINTF(DEBUG_ERROR, "No sid found on probe result \n");
		return; // should never happen 
	}
	
	DPRINTF(DEBUG_INFO, "bg-probe to sid = %d result was: %d \n", sid, succeeded);

	bg_probe_info info;
	bg_get_probe_info(db, sid, &info);
	if(info.sid == NO_SERVICE) {
		DPRINTF(DEBUG_ERROR, "No bg-probe-info found for sid = %d\n", sid);
		return; // should never happen
	}
 
	// update last success
	if(succeeded) {
		info.last_success = time;
	}else if((time - info.last_success) > BG_MAX_UNREACH_TIME) {
		DPRINTF(DEBUG_ERROR, "Reached limit for bg-probes to "
			" sid = %d.  Removing \n", sid);
		bg_remove_probe_info(db, sid);
		return;	

	}
	
	// in the future, adjust the 'wait' times
	// to do binary exponential back-off
	info.next_probe = time + BG_PROBE_INTERVAL;

	bg_update_entry(db, &info);
}


