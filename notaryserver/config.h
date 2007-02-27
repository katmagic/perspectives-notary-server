#ifndef _CONFIG_H_
#define _CONFIG_H_

#include "../common.h"
#include <sqlite3.h>
#include <vector.h>
#include <openssl/ssl.h>

typedef struct {

	int server_sock;
//	sqlite3* ssh_db;
//	sqlite3* probe_server_db;
	vector<SSL*> probe_servers;	
} config_data;



#endif
