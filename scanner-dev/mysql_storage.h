#ifndef _DB_STORAGE_H_
#define _DB_STORAGE_H_

#include "../common.h"
#include "mysql.h"


#define NO_SERVICE -1
#define NO_KEY -2

int get_last_obs_time(MYSQL *mysql, char* dns_name, uint16_t port,
	uint16_t type);

int get_service_id(MYSQL *mysql, char* dns_name, uint16_t port);

int get_key_id(MYSQL *mysql, char* blob, int blob_len, int key_type);

Key *get_key(MYSQL *mysql, int kid);

int get_service_info(MYSQL *mysql, int sid, char** dns_name, uint16_t* port);

void add_new_service(MYSQL *mysql, char *dns_name, uint16_t port);

void store_ssh_probe_result(MYSQL *mysql, char *dns_name, uint16_t port,
	uint32_t ip_addr, Key *key, int timestamp) ;


void insert_observation(MYSQL *mysql, int sid, int kid, 
		int timestamp, uint32_t ip_addr);


ssh_result_list* get_all_observations(MYSQL *mysql,
                char* dns_name, uint16_t port, uint16_t key_type);

MYSQL * open_mysql_conn(char *server, char *user, char* password,
		char *database);

void close_mysql_conn(MYSQL *mysql);



#endif
