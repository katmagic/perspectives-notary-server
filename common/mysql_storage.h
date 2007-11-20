#ifndef _DB_STORAGE_H_
#define _DB_STORAGE_H_

#include "common.h"
#include "mysql.h"


#define NO_SERVICE -1
#define NO_KEY -2
#define NO_VERSION -3

void update_timespan(MYSQL *mysql, int sid, int kid, int timestamp);

void record_failure(MYSQL *mysql, char *dns_name, int time, int exit_code);

int delete_from(MYSQL *mysql, char *table_name, char *match_row,
    char *match_str);

int get_last_obs_time(MYSQL *mysql, char* dns_name, uint16_t port,
	uint16_t type);

int get_service_id(MYSQL *mysql, char* dns_name, uint16_t port);

int get_key_id(MYSQL *mysql, char* blob, int blob_len, int key_type);

void get_key(MYSQL *mysql, int kid, char** buf_out, int* buf_len_out, 
                            int* key_type_out);

int get_service_info(MYSQL *mysql, int sid, char** dns_name, uint16_t* port);

void add_new_service(MYSQL *mysql, char *dns_name, uint16_t port);

void store_ssh_probe_result(MYSQL *mysql, char *dns_name, uint16_t port,
	uint32_t ip_addr, char *key_ptr, int key_len, int key_type,
        int timestamp, char* version_str) ;


void insert_observation(MYSQL *mysql, int sid, int kid, 
		int timestamp, uint32_t ip_addr, short vid);

ssh_key_info_list* get_key_info(MYSQL* mysql, int sid);

/*
ssh_result_list* get_all_observations(MYSQL *mysql,
                char* dns_name, uint16_t port, uint16_t key_type);
*/

MYSQL * open_mysql_conn(char *server, char *user, char* password,
		char *database);

void close_mysql_conn(MYSQL *mysql);


void create_all_tables(MYSQL *mysql);

void update_signature(MYSQL *mysql, int sid, char*sig, 
                                        unsigned int sig_len);
void get_sid_and_sig(MYSQL *mysql, char *dns_name, char* buf_out, 
                            int* buf_len_out, 
                            int* sid_out);

#endif
