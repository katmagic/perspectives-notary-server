#include <stdlib.h>
#include <string.h>

#include "xmalloc.h"
#include "mysql_storage.h"
#include "mysql.h"
#include "notary_util.h"



static Key *tmp_buf_to_key(char* buf, int buf_len, int key_type) {

	if(key_type == KEY_RSA1) {
		Buffer msg;
		buffer_init(&msg);
		buffer_append(&msg, buf, (u_int)buf_len);

        	(void) buffer_get_int(&msg); // ignored

		Key *key = key_new(KEY_RSA1);
	        buffer_get_bignum(&msg, key->rsa->e);
        	buffer_get_bignum(&msg, key->rsa->n);
		return key;
		
	} else {
		return key_from_blob((u_char*)buf, buf_len);
	}

}



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
			" time INTEGER, ip_addr INTEGER, vid SMALLINTEGER)";
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

	char query_buf[1024];
	snprintf(query_buf, 1024, "SELECT vid from version_id WHERE "
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
	if(stmt == NULL) {
          printf("bad stmt init \n");
          goto error;
        }

	char *select = "SELECT kid FROM key_id WHERE key_data = ? "
			" and type = ?";
	int error_code = mysql_stmt_prepare(stmt,select,strlen(select));
	if(error_code) {
          printf("bad stmt prepare : %d (%s) \n", error_code, mysql_error(mysql));
          goto stmt_error;
        }

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
	if(error_code) {
          printf("bad stmt bind param: %d \n", error_code);
          goto stmt_error;
        }

	error_code = mysql_stmt_execute(stmt);
	if(error_code) {
          printf("bad stmt execute: %d \n", error_code);
          goto stmt_error;
        }
	
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
        if(error_code) {
          printf("bad stmt bind result: %d \n", error_code);
          goto stmt_error;
        }
        error_code = mysql_stmt_fetch(stmt);
        if(error_code == MYSQL_NO_DATA) goto no_result;
        else if(error_code) {
           printf("bad stmt fetch: %d \n", error_code);
          goto stmt_error;
        }
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


/*
void get_key(MYSQL *mysql, int kid, char** buf_out, int* buf_len_out, 
                            int* key_type_out) {
	// use prepared statement, b/c otherwise i'm not sure how to
	// encode the blob data
	MYSQL_STMT* stmt = mysql_stmt_init(mysql);
	if(stmt == NULL) {
          printf("bad stmt init \n");
          goto error;
        }

	char *select = "SELECT key_data,type FROM key_id WHERE kid = ?";
	
	int error_code = mysql_stmt_prepare(stmt,select,strlen(select));
	if(error_code) {
          printf("bad stmt prepare : %d (%s) \n", error_code, mysql_error(mysql));
          goto stmt_error;
        }

	MYSQL_BIND bind_in[1];
	memset(bind_in, 0, sizeof(bind_in));
	my_bool not_null = 0;
	unsigned long var_sizes[1];
	var_sizes[0] = sizeof(int);
	
	bind_in[0].buffer_type = MYSQL_TYPE_LONG;
	bind_in[0].buffer = &kid;
	bind_in[0].buffer_length = var_sizes[0];
	bind_in[0].length = (unsigned long*)var_sizes[0];
	bind_in[0].is_null = &not_null;

	error_code = mysql_stmt_bind_param(stmt, bind_in);
	if(error_code) {
          printf("bad stmt bind param: %d \n", error_code);
          goto stmt_error;
        }

	error_code = mysql_stmt_execute(stmt);
	if(error_code) {
          printf("bad stmt execute: %d \n", error_code);
          goto stmt_error;
        }
	
        char key_buf[1024];
        unsigned long key_type_len = 100; 
        MYSQL_BIND bind_out[2];
       
	memset(&bind_out, 0, sizeof(bind_out));
	
        bind_out[0].buffer_type = MYSQL_TYPE_BLOB;
	bind_out[0].buffer = key_buf;
	bind_out[0].buffer_length = 1024;
	bind_out[0].length = (unsigned long*)buf_len_out;
	bind_out[0].is_null = &not_null;

	bind_out[1].buffer_type = MYSQL_TYPE_LONG;
	bind_out[1].buffer = key_type_out;
	bind_out[1].buffer_length = sizeof(int);
	bind_out[1].length = &key_type_len;
	bind_out[1].is_null = &not_null;

        error_code = mysql_stmt_bind_result(stmt, bind_out);
        if(error_code) {
          printf("bad stmt bind result: %d \n", error_code);
          goto stmt_error;
        }
        error_code = mysql_stmt_fetch(stmt);
        if(error_code == MYSQL_NO_DATA) goto no_result;
        else if(error_code) {
           printf("bad stmt fetch: %d \n", error_code);
          goto stmt_error;
        }

	mysql_stmt_close(stmt);
        printf("New: key len = %d  type = %d \n", *buf_len_out, *key_type_out);
        *buf_out = malloc(*buf_len_out);
        memcpy(*buf_out, key_buf, *buf_len_out);
        return;

	no_result:
                DPRINTF(DEBUG_INFO, "No result for KID \n");
		mysql_stmt_close(stmt);
		return;

	stmt_error:
		mysql_stmt_close(stmt);

	error: 
		DPRINTF(DEBUG_ERROR, "Error getting KID: %s \n", 
			mysql_error(mysql));
	
}
*/

void get_key(MYSQL *mysql, int kid, char** buf_out, int* buf_len_out, 
                            int* key_type_out) {


        *buf_out = NULL;
        *buf_len_out = -1;

        char query_buf[128];
	snprintf(query_buf, 128, "SELECT key_data,type FROM key_id WHERE kid = %d",
            kid);

	int error_code = 
		mysql_real_query(mysql, query_buf, strlen(query_buf));
	if(error_code) goto error;
	
	MYSQL_RES *result = mysql_store_result(mysql);
	if(!result) goto end;

	MYSQL_ROW row = mysql_fetch_row(result);
	if(row == NULL) goto end;
	if(row[0] == NULL) goto end;

   	unsigned long *lengths;
   	lengths = mysql_fetch_lengths(result);

	*buf_len_out = lengths[0];
	if(*buf_len_out <= 0) goto end;
	
        *buf_out = (char*) malloc(*buf_len_out);
	memcpy(*buf_out, row[0], *buf_len_out);
	*key_type_out = atoi(row[1]);

	end:
		mysql_free_result(result);
		return;	

	error: 
		fprintf(stderr, "Error looking up key: %s \n",
			mysql_error(mysql));
		return;
}


// NOTE: unlike getting keys from the database, this method assumes you have
// a buffer allocated.
void get_sid_and_sig(MYSQL *mysql, char *dns_name, char* buf_out, 
                            int* buf_len_out, 
                            int* sid_out) {

        *buf_len_out = -1;

        char query_buf[256];
	snprintf(query_buf, 256, "SELECT signature,sid FROM service_id WHERE dns_name = '%s'",
           dns_name);

	int error_code = 
		mysql_real_query(mysql, query_buf, strlen(query_buf));
	if(error_code) goto error;
	
	MYSQL_RES *result = mysql_store_result(mysql);
	if(!result) goto error;

	MYSQL_ROW row = mysql_fetch_row(result);
	if(row == NULL || row[0] == NULL){
            printf("no result in DB for: '%s' \n", dns_name);
            goto end;
        }

   	unsigned long *lengths;
   	lengths = mysql_fetch_lengths(result);

	*buf_len_out = lengths[0];
	if(*buf_len_out <= 0) {
          printf("invalid length from mysql: %ld \n", lengths[0]);
          goto end;
        }
	
	memcpy(buf_out, row[0], *buf_len_out);
	*sid_out = atoi(row[1]);

	end:
		mysql_free_result(result);
		return;	

	error: 
		fprintf(stderr, "Error looking up sig + sid of %s: %s \n",
			dns_name, mysql_error(mysql));
		return;
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
// NOTE: currently assumes dns_name uniquely identifies a service
// this makes adding new entries from quick_scan a bit faster/easier
void add_new_service(MYSQL *mysql, char *dns_name, uint16_t port) {

	char query_buf[128];
	snprintf(query_buf, 128, 
	"INSERT IGNORE into service_id(dns_name, port) values ('%s', %d)",
		dns_name, port);
	
	DPRINTF(DEBUG_INFO,
		"inserting new service %s : %d \n", dns_name, port);

	if(mysql_real_query(mysql, query_buf, strlen(query_buf)) != 0){
		fprintf(stderr, "Error inserting new service: %s \n",
			mysql_error(mysql));
		return;
	}

}

// generic delete method
// NOTE: if you are deleting strings, match_str should already 
// contain the literals, otherwise the query will fail
int delete_from(MYSQL *mysql, char *table_name, char *match_row,
    char *match_str) {

	char query_buf[128];
	snprintf(query_buf, 128, "Delete from %s where %s = %s",
		table_name, match_row, match_str);

	if(mysql_real_query(mysql, query_buf, strlen(query_buf)) != 0){
		fprintf(stderr, "Error executing delete : %s \n",
			mysql_error(mysql));
		return -1;
	}
      return mysql_affected_rows(mysql);
}

// add a new entry to the version_id table 
void add_new_version(MYSQL *mysql, char *version_str) {

        // note: some version strings are LONG...
	char query_buf[1024];
	snprintf(query_buf, 1024, 
	"INSERT into version_id(version_str) values ('%s')",version_str);
	
	if(mysql_real_query(mysql, query_buf, strlen(query_buf)) != 0){
		fprintf(stderr, "Error inserting new version: %s \n",
			mysql_error(mysql));
		return;
	}
}


void update_signature(MYSQL *mysql, int sid, char*sig, 
                                        unsigned int sig_len) {

	// use prepared statement, b/c otherwise i'm not sure how to
	// encode the blob data
	MYSQL_STMT* stmt = mysql_stmt_init(mysql);
	if(stmt == NULL) goto error;

	char *select = "UPDATE service_id set signature = ? where sid = ?";
	int error_code = mysql_stmt_prepare(stmt,select,strlen(select));
	if(error_code) goto stmt_error;

	MYSQL_BIND bind[2];
	memset(bind, 0, sizeof(bind));
	my_bool not_null = 0;
	unsigned long var_sizes[2];
	var_sizes[0] = sig_len;
	var_sizes[1] = sizeof(int);

	bind[0].buffer_type = MYSQL_TYPE_BLOB;
	bind[0].buffer = sig;
	bind[0].buffer_length = var_sizes[0];
	bind[0].length = (unsigned long*)&var_sizes[0];
	bind[0].is_null = &not_null;

	bind[1].buffer_type = MYSQL_TYPE_LONG;
	bind[1].buffer = &sid;
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
            fprintf(stderr, "Error adding signature for sid %d : %s \n", 
                          sid, mysql_error(mysql));

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

void store_ssh_probe_result(MYSQL *mysql, char *dns_name, uint16_t port,
				uint32_t ip_addr, char *buf,
                                int buf_size, int key_type, 
                                int timestamp, char* version_str) {

	int kid = get_key_id(mysql, buf, buf_size, key_type);
	if(kid == NO_KEY) {
		// we've never seen this key before
		DPRINTF(DEBUG_DATABASE, "New key id for %s\n", dns_name);
		add_new_key(mysql, buf, buf_size, key_type);
		kid = get_key_id(mysql, buf, buf_size, key_type);
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
		if(vid == NO_VERSION) {
			DPRINTF(DEBUG_ERROR, 
                            "Error adding version ID for '%s' \n", version_str);
		}

	} // ignore errors for versions.  who cares.

        update_timespan(mysql, sid, kid, timestamp);
	insert_observation(mysql, sid, kid, timestamp, ip_addr, vid);
}

// add an entry to the 'timespans' table
// the first query assumes the key has not changed.  If so, exactly
// one row should have changed, and we exit.  Otherwise, we insert a 
// new timespan, and mark the old timespan as no longer current. 
void update_timespan(MYSQL *mysql, int sid, int kid, int timestamp) {

	DPRINTF(DEBUG_DATABASE, "updating timespan for sid = %d "
			" kid = %d\n", sid, kid);

	char query_buf[256];
	snprintf(query_buf, 256, "update timespans set t_end = %d "
              "where sid = %d and kid = %d and current = 1",
              timestamp, sid, kid);
	

	if(mysql_real_query(mysql, query_buf, strlen(query_buf)) != 0){
		fprintf(stderr, "Error updating timespan: %s \n",
			mysql_error(mysql));
		return;
	}
      
        int num_rows = mysql_affected_rows(mysql);

        if(num_rows == 1) 
          return;  // SUCCESSFUL UPDATE

        if(num_rows != 0) {
            printf("error: num_rows is %d for sid = %d \n", num_rows, sid);
            return;
        }

	DPRINTF(DEBUG_DATABASE, "adding new timespan for sid = %d "
			" kid = %d\n", sid, kid);
	
        snprintf(query_buf, 256, "update timespans set current = 0 where "
            " sid = %d and current = 1", sid);
        
	if(mysql_real_query(mysql, query_buf, strlen(query_buf)) != 0){
		fprintf(stderr, "Error clearing current bit in timespan: %s \n",
			mysql_error(mysql));
		return;
	}

	snprintf(query_buf, 256, "insert into timespans(sid,kid,t_start,t_end,current) values (%d,%d,%d,%d,1)",
              sid, kid,timestamp, timestamp);
	
        
	if(mysql_real_query(mysql, query_buf, strlen(query_buf)) != 0){
		fprintf(stderr, "Error adding new timespan: %s \n",
			mysql_error(mysql));
		return;
	}
      
        
}



// add an entry to the 'observations' table
// NOTE: this is now outdated, as keys are stored using key timespans
//  in the "timespans" table
void insert_observation(MYSQL *mysql, int sid, int kid,  
	int timestamp, uint32_t ip_addr, short vid) {

	DPRINTF(DEBUG_DATABASE, "adding observation for sid = %d "
			" kid = %d\n", sid, kid);

	char query_buf[128];
	snprintf(query_buf, 128, 
	"INSERT into observations(sid,kid,time,ip_addr,vid) values (%d, %d, %d, %d, %d)",
	sid, kid, timestamp, ip_addr, vid);
	

	if(mysql_real_query(mysql, query_buf, strlen(query_buf)) != 0){
		fprintf(stderr, "Error inserting new service: %s \n",
			mysql_error(mysql));
		return;
	}

}

ssh_key_info_list* get_key_info(MYSQL* mysql, int sid) {
	
        ssh_key_info_list *head = NULL;
        MYSQL_RES *result = NULL;

        char query_buf[256];
        snprintf(query_buf, 256, "select kid, t_start, t_end from timespans "
              "where sid = %d order by kid, t_start",sid);
	int error_code = 
		mysql_real_query(mysql, query_buf, strlen(query_buf));
	if(error_code) goto error;

	result = mysql_store_result(mysql);
	if(!result) goto end;

        int num_rows = mysql_num_rows(result);
        int* kids  = (int*)malloc(sizeof(int) * num_rows * 3);
        int *t_starts = kids + num_rows;
        int *t_ends = t_starts + num_rows;

	int i;
	for(i = 0; i < num_rows; i++) {
		MYSQL_ROW row = mysql_fetch_row(result);
		if(row == NULL || row[0] == NULL){
			DPRINTF(DEBUG_ERROR, "Couldn't access expect row in"
				" 'timespans'. quiting early. \n");
                        free(kids);
			goto end;
		}
		kids[i] = atoi(row[0]);
		t_starts[i] = atoi(row[1]);
		t_ends[i] = atoi(row[2]);
	} 
		
        mysql_free_result(result);
        head = (ssh_key_info_list*)malloc(sizeof(ssh_key_info_list));
        INIT_LIST_HEAD(&(head->list));

        int cur_kid = -1;
        for(i = 0; i < num_rows; i++) {
            if(cur_kid != kids[i]) {
              cur_kid = kids[i];
              int num_timespans = 0;
              int j;
              for(j = 0; j < num_rows; j++) 
                  if(kids[j] == cur_kid) ++num_timespans;

              char *key_buf;
              int key_len, key_type;
              get_key(mysql, cur_kid, &key_buf, &key_len, &key_type);

              Key *key = tmp_buf_to_key(key_buf, key_len, key_type);
              if(key == NULL){
                  printf("Error: KID = %d can't be converted to a key\n",
                      cur_kid);
                  printf("type = %d len = %d \n", key_type, key_len);
                  continue;
              }
              uint8_t *digest_raw;
              uint32_t digest_raw_len;
              digest_raw = key_fingerprint_raw(key, SSH_FP_MD5,
                                            &digest_raw_len);
              if(digest_raw == NULL){
                    printf("key fingerprint failed \n");
                    continue;
              }

              int key_info_size = sizeof(ssh_key_info) 
                                  + (sizeof(int)*num_timespans * 2)
                                  + digest_raw_len;
              ssh_key_info *info = (ssh_key_info*) 
                                        malloc(key_info_size);
              info->num_timespans = htons(num_timespans);
              info->key_len_bytes = htons(digest_raw_len);
              info->key_type = key_type;
              
              uint8_t *key_ptr = (uint8_t*)(info + 1);
              memcpy(key_ptr, digest_raw, digest_raw_len);
              
              free(key_buf);
              xfree(key);
              xfree(digest_raw);
              int *timespan_ptr = (int*)(key_ptr + digest_raw_len);
              for(j = i; kids[j] == cur_kid; j++) {
                   timespan_ptr[0] = htonl(t_starts[j]);
                   timespan_ptr[1] = htonl(t_ends[j]);
                   timespan_ptr += 2;
              }

              ssh_key_info_list* tmp = (ssh_key_info_list*)
                                        malloc(sizeof(ssh_key_info_list));
              tmp->info = info;
              __list_add(&(tmp->list),&(head->list), head->list.next);

            }
  
        }

        free(kids);
        return head;

	error: 
		fprintf(stderr, "Error looking up key: %s \n",
			mysql_error(mysql));
	end:
                if(result)
                  mysql_free_result(result);
		return head;

}

unsigned int 
get_reply_data(MYSQL *mysql, int sid, char* buf, int max_size) {
    
        int total_size = 0;
        ssh_key_info_list* info_list = NULL;
        struct list_head *pos,*tmp;
        ssh_key_info_list* cur;

        int num_keys = 0;
        if(sid == NO_SERVICE) return 0;

        info_list = get_key_info(mysql, sid);

        if(info_list == NULL) return 0;   

        list_for_each_safe(pos, tmp, &info_list->list) {
            cur = list_entry(pos, ssh_key_info_list, list);
            total_size += KEY_INFO_SIZE(cur->info);
            ++num_keys;
        } 

        int offset = 0;
        list_for_each_safe(pos, tmp, &info_list->list) {
            cur = list_entry(pos, ssh_key_info_list, list);  
            int size = KEY_INFO_SIZE(cur->info);


            if(offset + size <= max_size)
                memcpy(buf + offset, cur->info, size);
            else {
                DPRINTF(DEBUG_ERROR, 
                    "insufficient space for reply to sid = %d \n", sid);
                return size;
            }
                
          offset += size;
            
       }
        
       printf("warning. leaking info_list on purpose! \n");
       //free_key_info_list(info_list);
       return total_size;
}



// results a ssh_result_list with all observations
// for this key-id, as well as the key itself
/*
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
*/

// returns a list of 'ssh_result_list' structs that represent 
// all key observations associated with the specified 'dns_name/port'
// the caller must remember to free the memory allocated for list
// elements
/*
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
*/

MYSQL * open_mysql_conn(char *server, char *user, char* password,
		char *database) {

       MYSQL *mysql = mysql_init(NULL);

       /* Connect to database */
       if (!mysql_real_connect(mysql, server,
             user, password, database, 0, NULL, CLIENT_FOUND_ROWS)) {
          fprintf(stderr, "%s\n", mysql_error(mysql));
          exit(0);
       }
        return mysql;
}


// closes the database file 
void close_mysql_conn(MYSQL *mysql) {
  mysql_close(mysql);
}

void record_failure(MYSQL *mysql, char *dns_name, int time, int exit_code) {

	char query_buf[1024];
	snprintf(query_buf, 128, 
	"INSERT into failures(dns_name, time, exit_code) values ('%s',%d,%d)",
              dns_name, time, exit_code);
	
	if(mysql_real_query(mysql, query_buf, strlen(query_buf)) != 0){
		fprintf(stderr, "Error inserting new version: %s \n",
			mysql_error(mysql));
		return;
	}
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

