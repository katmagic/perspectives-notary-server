
#include "background_probing.h"
#include "db_storage.h"
#include "ssh-keyscan.h"
#include "../debug.h"

#define NUM_HOLDERS 1024

unsigned int notary_debug = DEBUG_ALL;

int main(int argc, char** argv) {

	init_scankeys();
	sqlite3* db = db_init("ssh_notary1.db");
	ssh_key_holder ssh_keys[NUM_HOLDERS];

	char* host = "linux1.gp.cs.cmu.edu";
	uint16_t port = 22;
	int sid = get_service_id(db, host, port);
	
	if(sid == NO_SERVICE) {
		add_new_service(db, host, port);
		sid = get_service_id(db,host,port);
	}

	if(!bg_already_in_table(db, sid))	
		bg_add_new_service(db, sid);

	struct timeval cur_time;
	gettimeofday(&cur_time, NULL);
	int time = (uint32_t) cur_time.tv_sec;

	
	bg_run_periodic_probes(db,time); 	

	printf("entering loop \n");
	// loop infinitely to process all probe results
	while(1) {


		int num_holders_used = conloop(ssh_keys, NUM_HOLDERS);
	
		if(num_holders_used > 0) {	
		

			for(int i = 0; i < num_holders_used; i++) {
				ssh_key_holder *h = (&ssh_keys[i]);

				BOOL success = FALSE;
				if(h->key != NULL) {
					store_ssh_probe_result(db, h->name, 
						h->port, h->ip_addr, h->key, time) ;
					success = TRUE;
				}
				bg_probe_result(db, h->name, h->port, success);
				printf("done probing %s : %d \n", h->name, h->port);

			}
		}

	
  	} // end while

	// never reached
	db_close(db);
}


