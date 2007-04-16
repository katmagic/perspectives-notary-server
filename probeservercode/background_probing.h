#ifndef _BACKGROUND_PROBING_H_
#define _BACKGROUND_PROBING_H_

#include "../common.h"
#include <sqlite3.h>


#define BG_CHECK_INTERVAL (600) // 10 minutes

#define BG_PROBE_INTERVAL (3600 * 24) // 1 day

#define BG_MAX_UNREACH_TIME (BG_PROBE_INTERVAL * 4) // 4 days

#define NEVER_SEEN 0


// just for internal use
typedef struct {
	int sid;
	int next_probe;
	int wait;
	int last_success;
} bg_probe_info;


void bg_probe_result(sqlite3* db, char* dns_name, uint16_t port, BOOL succeeded);
void bg_run_periodic_probes(sqlite3 *db, int cur_time);
void bg_get_probe_info(sqlite3 *db, int sid, bg_probe_info *info);
void bg_remove_probe_info(sqlite3 *db, int sid);
void bg_update_entry(sqlite3* db, bg_probe_info *info);
void bg_add_new_service(sqlite3 *db, int sid);
BOOL bg_already_in_table(sqlite3 *db, int sid);

#endif
