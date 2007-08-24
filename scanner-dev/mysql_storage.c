#include <stdlib.h>
#include <string.h>

#include "xmalloc.h"
#include "mysql_storage.h"
#include "../util/key_util.h"
#include "mysql.h"

// create the 'ssh_key_bindings' table if it does not already exist
void create_table(char* create_stmt, MYSQL *mysql) {

	if(mysql_real_query(mysql, create_stmt, strlen(create_stmt)) != 0){
		fprintf(stderr, "Failed creating table with stmt: \n %s \n",
			create_stmt);
		fprintf(stderr, "Error was: %s \n", mysql_error(mysql));
	}
}

void create_all_tables(MYSQL *mysql) {

	char *create_service_id = "CREATE TABLE IF NOT EXISTS service_id "
			"(sid INTEGER PRIMARY KEY AUTO_INCREMENT, "
			"dns_name VARCHAR(100), port INTEGER)";
	create_table(create_service_id, mysql);

	char *create_key_id = "CREATE TABLE IF NOT EXISTS key_id "
			"(kid INTEGER PRIMARY KEY AUTO_INCREMENT, "
			" key_data BLOB, type INTEGER)";
	create_table(create_key_id, mysql);

	char *create_observations = "CREATE TABLE IF NOT EXISTS" 
			" observations (sid INTEGER, kid INTEGER," 
			" time INTEGER, ip_addr INTEGER)";
	create_table(create_observations, mysql);

	char *create_background_probes = "CREATE TABLE IF NOT EXISTS" 
			" background_probes (sid INTEGER, "
			" next_probe INTEGER, wait INTEGER, " 
			" last_success INTEGER)";
	create_table(create_background_probes, mysql);

	char *create_exceptions = "CREATE TABLE IF NOT EXISTS"
		" exceptions (prefix VARCHAR(18), source VARCHAR(100), "
		" started TIMESTAMP DEFAULT CURRENT_TIMESTAMP) ";
	create_table(create_exceptions, mysql);

        char *create_version_id = "CREATE TABLE IF NOT EXISTS"
              "version_id (vid SMALLINT PRIMARY KEY AUTO_INCREMENT, "
              "version_str varchar(64)) ";
        create_table(create_version_id, mysql);
}	


int get_last_obs_time(MYSQL *mysql, char* dns_name, uint16_t port,
		uint16_t type) {

	int sid = get_service_id(mysql, dns_name, port);
	if(sid == NO_SERVICE) 
		return NO_SERVICE;	 
	char query_buf[128];

	snprintf(query_buf, 128, "SELECT max(time) FROM key_id,observations "
			"where sid = %d and key_id.kid = observations.kid "
			" and type = %d", sid, type);
	
	if(mysql_real_query(mysql, query_buf, strlen(query_buf)) != 0) {
		fprintf(stderr, "Error on observation query: %s \n",
			mysql_error(mysql));
		return NO_KEY;
	}	


	int ret_value = NO_KEY;
	MYSQL_RES *result = mysql_store_result(mysql);
	if(!result) goto end;

	MYSQL_ROW row = mysql_fetch_row(result);
	if(row == NULL) goto end;
	if(row[0] == NULL) goto end;

	ret_value = atoi(row[0]);

	end:
		mysql_free_result(result);
		return ret_value;	
	
}


int get_service_id(MYSQL *mysql, char* dns_name, uint16_t port) {

	char query_buf[128];

	snprintf(query_buf, 128, "SELECT sid from service_id WHERE "
			"dns_name = '%s' and port = %d",dns_name, port);

	if(mysql_real_query(mysql, query_buf, strlen(query_buf)) != 0) {
		fprintf(stderr, "Query found nothing: %s \n",
			mysql_error(mysql));
		return NO_SERVICE;
	}	
	
	int ret_value = NO_SERVICE;

	MYSQL_RES *result = mysql_store_result(mysql);
	if(!result) goto end;

	MYSQL_ROW row = mysql_fetch_row(result);
	if(row == NULL) goto end;
	if(row[0] == NULL) goto end;

	ret_value = atoi(row[0]);

	end:
		mysql_free_result(result);
		return ret_value;	

}

short get_version_id(MYSQL *mysql, char* version_str) {

	char query_buf[128];
	snprintf(query_buf, 128, "SELECT sid from service_id WHERE "
			"version_str = '%s'", version_str);
	if(mysql_real_query(mysql, query_buf, strlen(query_buf)) != 0) {
		fprintf(stderr, "version_id query failed: %s \n",
			mysql_error(mysql));
		return NO_VERSION;
	}	
	
	int ret_value = NO_VERSION;
	MYSQL_RES *result = mysql_store_result(mysql);
	if(!result) goto end;

	MYSQL_ROW row = mysql_fetch_row(result);
	if(row == NULL) goto end;
	if(row[0] == NULL) goto end;
	ret_value = atoi(row[0]);

	end:
		mysql_free_result(result);
		return ret_value;	
}


int get_key_id(MYSQL *mysql, char* blob, int blob_len, int key_type) {

	// use prepared statement, b/c otherwise i'm not sure how to
	// encode the blob data
	MYSQL_STMT* stmt = mysql_stmt_init(mysql);
	if(stmt == NULL) goto error;

	char *select = "SELECT kid FROM key_id WHERE key_data = ? "
			" and type = ?";
	int error_code = mysql_stmt_prepare(stmt,select,strlen(select));
	if(error_code) goto stmt_error;

	MYSQL_BIND bind_in[2];
	memset(bind_in, 0, sizeof(bind_in));
	my_bool not_null = 0;
	unsigned long var_sizes[2];
	var_sizes[0] = blob_len;
	var_sizes[1] = sizeof(int);
	
	bind_in[0].buffer_type = MYSQL_TYPE_BLOB;
	bind_in[0].buffer = blob;
	bind_in[0].buffer_length = var_sizes[0];
	bind_in[0].length = (unsigned long*)&var_sizes[0];
	bind_in[0].is_null = &not_null;

	bind_in[1].buffer_type = MYSQL_TYPE_LONG;
	bind_in[1].buffer = &key_type;
	bind_in[1].buffer_length = var_sizes[1];
	bind_in[1].length = (unsigned long*)var_sizes[1];
	bind_in[1].is_null = &not_null;

	error_code = mysql_stmt_bind_param(stmt, bind_in);
	if(error_code) goto stmt_error;

	error_code = mysql_stmt_execute(stmt);
	if(error_code) goto stmt_error;
	
        int kid; 
        unsigned long kid_len;
        my_bool kid_null;
        MYSQL_BIND bind_out[1];
	memset(&bind_out, 0, sizeof(bind_out));

	bind_out[0].buffer_type = MYSQL_TYPE_LONG;
	bind_out[0].buffer = &kid;
	bind_out[0].buffer_length = sizeof(int);
	bind_out[0].length = (unsigned long*)&kid_len;
	bind_out[0].is_null = &kid_null;

        error_code = mysql_stmt_bind_result(stmt, bind_out);
        if(error_code) goto stmt_error;

        error_code = mysql_stmt_fetch(stmt);
        if(error_code == MYSQL_NO_DATA) goto no_result;
        else if(error_code) goto stmt_error;

        if(bind_out[0].buffer_type != MYSQL_TYPE_LONG) {
            DPRINTF(DEBUG_ERROR, "Unexpected type for kid: %d \n", 
                      bind_out[0].buffer_type);
                      goto stmt_error;
        }

	mysql_stmt_close(stmt);
	return kid;
	
	no_result:
                DPRINTF(DEBUG_INFO, "No result for KID \n");
		mysql_stmt_close(stmt);
		return NO_KEY;

	stmt_error:
		mysql_stmt_close(stmt);

	error: 
		DPRINTF(DEBUG_ERROR, "Error getting KID: %s \n", 
			mysql_error(mysql));
		return NO_KEY;

}

Key *get_key(MYSQL *mysql, int kid) {
	

	char query_buf[128];
	snprintf(query_buf, 128, 
	"SELECT key_data, type FROM key_id WHERE kid = %d", kid);

	int error_code = 
		mysql_real_query(mysql, query_buf, strlen(query_buf));
	if(error_code) goto error;
	
	Key* ret_value = NULL;

	MYSQL_RES *result = mysql_store_result(mysql);
	if(!result) goto end;

	MYSQL_ROW row = mysql_fetch_row(result);
	if(row == NULL) goto end;
	if(row[0] == NULL) goto end;

   	unsigned long *lengths;
   	lengths = mysql_fetch_lengths(result);

	int buf_size = lengths[0];
	if(buf_size <= 0) goto end;
	
	char* buf = (char*) row[0];
	int key_type = atoi(row[1]);
	ret_value = buf_to_key(buf, buf_size, key_type);

	end:
		mysql_free_result(result);
		return ret_value;	

	error: 
		fprintf(stderr, "Error looking up key: %s \n",
			mysql_error(mysql));
		return NULL;

}

int get_service_info(MYSQL *mysql, int sid, char** dns_name, 
		uint16_t* port) {

	char query_buf[128];
	snprintf(query_buf, 128, 
	"SELECT dns_name, port FROM service_id WHERE sid = %d", sid);

	int error_code = 
		mysql_real_query(mysql, query_buf, strlen(query_buf));
	if(error_code) goto error;
	
	int ret_value = NO_SERVICE;

	MYSQL_RES *result = mysql_store_result(mysql);
	if(!result) goto end;

	MYSQL_ROW row = mysql_fetch_row(result);
	if(row == NULL) goto end;
	if(row[0] == NULL) goto end;

   	unsigned long *lengths;
   	lengths = mysql_fetch_lengths(result);

	int buf_size = lengths[0];
	if(buf_size <= 0) goto end;

	*dns_name = (char*) malloc(buf_size + 1);
	strncpy(*dns_name, row[0], buf_size + 1);
	
	*port = atoi(row[1]);
	ret_value = 1; // success

	end:
		mysql_free_result(result);
		return ret_value;	

	error: 
		fprintf(stderr, "Error looking up key: %s \n",
			mysql_error(mysql));
		return NO_SERVICE;

}


// add a new entry to the service_id table 
void add_new_service(MYSQL *mysql, char *dns_name, uint16_t port) {

	char query_buf[128];
	snprintf(query_buf, 128, 
	"INSERT into service_id(dns_name, port) values ('%s', %d)",
		dns_name, port);
	
	DPRINTF(DEBUG_INFO,
		"inserting new service %s : %d \n", dns_name, port);

	if(mysql_real_query(mysql, query_buf, strlen(query_buf)) != 0){
		fprintf(stderr, "Error inserting new service: %s \n",
			mysql_error(mysql));
		return;
	}

}

// add a new entry to the version_id table 
void add_new_version(MYSQL *mysql, char *version_str) {

	char query_buf[128];
	snprintf(query_buf, 128, 
	"INSERT into version_id(version_str) values ('%s')",version_str);
	
	if(mysql_real_query(mysql, query_buf, strlen(query_buf)) != 0){
		fprintf(stderr, "Error inserting new version: %s \n",
			mysql_error(mysql));
		return;
	}
}



void add_new_key(MYSQL *mysql, char*blob, int blob_len, int key_type) {

	// use prepared statement, b/c otherwise i'm not sure how to
	// encode the blob data
	MYSQL_STMT* stmt = mysql_stmt_init(mysql);
	if(stmt == NULL) goto error;

	char *select = "INSERT into key_id(key_data,type)  values (?, ?)";
	int error_code = mysql_stmt_prepare(stmt,select,strlen(select));
	if(error_code) goto stmt_error;

	MYSQL_BIND bind[2];
	memset(bind, 0, sizeof(bind));
	my_bool not_null = 0;
	unsigned long var_sizes[2];
	var_sizes[0] = blob_len;
	var_sizes[1] = sizeof(int);
	
	bind[0].buffer_type = MYSQL_TYPE_BLOB;
	bind[0].buffer = blob;
	bind[0].buffer_length = var_sizes[0];
	bind[0].length = (unsigned long*)&var_sizes[0];
	bind[0].is_null = &not_null;

	bind[1].buffer_type = MYSQL_TYPE_LONG;
	bind[1].buffer = &key_type;
	bind[1].buffer_length = var_sizes[1];
	bind[1].length = (unsigned long*)&var_sizes[1];
	bind[1].is_null = &not_null;

	error_code = mysql_stmt_bind_param(stmt, bind);
	if(error_code) goto stmt_error;

	error_code = mysql_stmt_execute(stmt);
	if(error_code) goto stmt_error;
		
	mysql_stmt_close(stmt);
        return;

	stmt_error:
		mysql_stmt_close(stmt);

	error: 
		fprintf(stderr, "Error adding new KID: %s \n", 
			mysql_error(mysql));

}

// dw: what are these TODOs talking about? 
		// TODO: fix join code so only correct key type is returned
		// TODO: add periodic probing
void store_ssh_probe_result(MYSQL *mysql, char *dns_name, uint16_t port,
				uint32_t ip_addr, Key *key, int timestamp,
                                 char* version_str) {
	if(key == NULL){
		printf("no key to store \n");
		return;
	}

	char* buf;
	int buf_size = 0;
	key_to_buf(key, &buf, &buf_size);

	int kid = get_key_id(mysql, buf, buf_size, key->type);
	if(kid == NO_KEY) {
		// we've never seen this key before
		DPRINTF(DEBUG_DATABASE, "New key id for %s\n", dns_name);
		add_new_key(mysql, buf, buf_size, key->type);
		kid = get_key_id(mysql, buf, buf_size, key->type);
		if(kid == NO_KEY) {
			DPRINTF(DEBUG_ERROR, "Error adding key ID \n");
			return;
		}
		
	}

	int sid = get_service_id(mysql, dns_name, port);
	if(sid == NO_SERVICE) {
		// we've never seen this service before
		DPRINTF(DEBUG_DATABASE, "New service id for %s: %d\n", 
				dns_name, port);
		add_new_service(mysql, dns_name, port);
		sid = get_service_id(mysql, dns_name, port);
		if(sid == NO_SERVICE) {
			DPRINTF(DEBUG_ERROR, "Error adding service ID \n");
			return;
		}
		
	}

        short vid = get_version_id(mysql, version_str);
	if(vid == NO_VERSION) {
		add_new_version(mysql, version_str);
		vid = get_version_id(mysql, version_str);
	} // ignore errors for versions.  who cares.

	insert_observation(mysql, sid, kid, timestamp, ip_addr, vid);
	xfree(buf);
}


// add an entry to the 'observations' table
void insert_observation(MYSQL *mysql, int sid, int kid,  
	int timestamp, uint32_t ip_addr, short vid) {

	DPRINTF(DEBUG_DATABASE, "adding observation for sid = %d "
			" kid = %d\n", sid, kid);

	char query_buf[128];
	snprintf(query_buf, 128, 
	"INSERT into observations(sid,kid,time,ip_addr) values (%d, %d, %d, %d)",
	sid, kid, timestamp, ip_addr);
	

	if(mysql_real_query(mysql, query_buf, strlen(query_buf)) != 0){
		fprintf(stderr, "Error inserting new service: %s \n",
			mysql_error(mysql));
		return;
	}

}

// results a ssh_result_list with all observations
// for this key-id, as well as the key itself
ssh_result_list *get_observations_for_key(MYSQL* mysql, int kid) {
		
	Key *key = get_key(mysql, kid);
	if(key == NULL) {
		DPRINTF(DEBUG_ERROR, "Unable to access kid = %d "
			" from DB \n", kid);
		return NULL;
	}
	ssh_result_list* observations = (ssh_result_list*)
				malloc(sizeof(ssh_result_list));
	observations->key = key;
	
	char query_buf[128];
	snprintf(query_buf, 128, 
	"SELECT count(*) FROM observations where kid = %d", kid);

	int error_code = 
		mysql_real_query(mysql, query_buf, strlen(query_buf));
	if(error_code) goto error;
	
	ssh_result_list *ret_value = NULL;

	MYSQL_RES *result = mysql_store_result(mysql);
	if(!result) goto end;

	MYSQL_ROW row = mysql_fetch_row(result);
	if(row == NULL) goto end;
	if(row[0] == NULL) goto end;

	int total_count = atoi(row[1]);
	DPRINTF(DEBUG_MESSAGE, "we have %d total timestamps \n", 
				total_count);

	observations->num_probes = total_count;
	observations->timestamps = (int*) malloc(sizeof(int) * total_count);
	observations->addresses = (int*) malloc(sizeof(int) * total_count);

	snprintf(query_buf, 128, "SELECT time, ip_addr FROM observations "
	"where kid = %d order by time", kid);

	error_code = 
		mysql_real_query(mysql, query_buf, strlen(query_buf));
	if(error_code) goto error2;

	result = mysql_store_result(mysql);
	if(!result) goto end;

	int i;
	for(i = 0; i < total_count; i++) {
		MYSQL_ROW row = mysql_fetch_row(result);
		if(row == NULL || row[0] == NULL){
			DPRINTF(DEBUG_ERROR, "Couldn't access expect row in"
				" 'ssh_probes'. quiting early. \n");
			observations->num_probes = i; // only valid through i
			goto end;
		}
		int t = atoi(row[0]);
		int a = atoi(row[1]);
		observations->timestamps[i] = htonl(t); // that's dumb !!!
		observations->addresses[i] = a;
	} 

	ret_value = observations;
	
	end:
		mysql_free_result(result);
		return ret_value;	

	error2:
		mysql_free_result(result);
		free(observations->timestamps);
		free(observations->addresses);
	error: 
		fprintf(stderr, "Error looking up key: %s \n",
			mysql_error(mysql));
		return NULL;
}


// returns a list of 'ssh_result_list' structs that represent 
// all key observations associated with the specified 'dns_name/port'
// the caller must remember to free the memory allocated for list
// elements
ssh_result_list* get_all_observations(MYSQL *mysql,
		char* dns_name, uint16_t port, uint16_t key_type) {


	DPRINTF(DEBUG_DATABASE, "DB look-up for dns-name = %s  "
		" with key-type = %d \n", dns_name, key_type);
	int sid = get_service_id(mysql, dns_name, port);
	if(sid == NO_SERVICE){
		DPRINTF(DEBUG_ERROR, "Found no service for %s : %d \n", 
			dns_name, port);
		return NULL;
	}
	
	ssh_result_list* head = (ssh_result_list*)
		malloc(sizeof(ssh_result_list));
	INIT_LIST_HEAD(&(head->list));
	
	char query_buf[128];
	snprintf(query_buf, 128, 
	"SELECT DISTINCT kid FROM observations,key_id where sid = %d "
		" and key_type = %d ", sid, key_type);

	int ret_code = mysql_real_query(mysql, query_buf, strlen(query_buf));
	if(ret_code) goto error;
	
	ssh_result_list* ret_value = NULL;

	MYSQL_RES *result = mysql_store_result(mysql);
	if(!result) goto end;

	// loop once for each unique key that we have seen for this
	// service identifier
	int num_keys = 0; 
	while(1) {
		MYSQL_ROW row = mysql_fetch_row(result);
		if(row == NULL) break;
		if(row[0] == NULL) break;
		num_keys++;

		int kid = atoi(row[0]);
		ssh_result_list *result = 
			get_observations_for_key(mysql, kid);

		__list_add(&(result->list),&(head->list), head->list.next );
		
	} // end ROW for-loop
	DPRINTF(DEBUG_INFO, "Found total of %d keys \n", num_keys);

	ret_value = head;
	
	end:
		mysql_free_result(result);
		return ret_value;	

	error: 
		free(head);
		fprintf(stderr, "Error looking up key: %s \n",
			mysql_error(mysql));
		return NULL;
}


MYSQL * open_mysql_conn(char *server, char *user, char* password,
		char *database) {

       MYSQL *mysql = mysql_init(NULL);

       /* Connect to database */
       if (!mysql_real_connect(mysql, server,
             user, password, database, 0, NULL, 0)) {
          fprintf(stderr, "%s\n", mysql_error(mysql));
          exit(0);
       }
        return mysql;
}


// closes the database file 
void close_mysql_conn(MYSQL *mysql) {
  mysql_close(mysql);
}

/*
//TEST CODE ONLY. 

unsigned int notary_debug = DEBUG_INFO | DEBUG_MESSAGE | DEBUG_ERROR;

int main(int argc, char** argv) {

	printf("loading mysql \n");

	MYSQL *mysql = open_mysql_conn("localhost", "root",
		"moosaysthecow", "ssh");

	printf("adding tables \n");

	create_all_tables(mysql);

	mysql_close(mysql);

  	return 0;
}

*/

