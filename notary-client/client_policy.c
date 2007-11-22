
#include "client_policy.h"

BOOL check_quorum_duration(SSHNotary *notary, char *key_data, uint16_t key_len, uint8_t key_type,  
                                    int quorum_size, uint32_t duration_sec, 
                                    uint32_t stale_limit_sec) {

        struct timeval now;
        gettimeofday(&now, NULL);
        
        int total_valid = 0;

	struct list_head *outer_pos, *inner_pos;
	server_list *server;
	list_for_each(outer_pos,&notary->notary_servers.list){
		server = list_entry(outer_pos, server_list, list);
		ssh_key_info_list *elem;
                if(server->notary_results == NULL) {
                  //printf("no results for server \n");
                  continue;
                }

                uint32_t most_recent_start = 0;
                uint32_t most_recent_end = 0;
                // find most recent key
		ssh_key_info *most_recent = NULL; 
                list_for_each(inner_pos,&(server->notary_results->list)) {
			elem = list_entry(inner_pos, ssh_key_info_list, list);
			ssh_key_info *info = elem->info;
                        int *timespans = FIND_TIMESPANS(info);
                        for(int i = 0; i < info->num_timespans * 2; i = i + 2) {
                              uint32_t start = timespans[i];
                              uint32_t end = timespans[i + 1];
                              if(end > most_recent_end) {
                                  most_recent_start = start;
                                  most_recent_end = end;
                                  most_recent = info; 
                              }
                        }
		}

                if(most_recent == NULL) {
                  DPRINTF(DEBUG_ERROR,"Failed to find most recent timespan\n");
                  continue;
                }
   
                if(key_type != most_recent->key_type) continue;
                if(key_len != ntohs(most_recent->key_len_bytes)) continue;
                          
                char *key_buf = (char*)(most_recent + 1);
                if(memcmp(key_data, key_buf, key_len)) continue;

                uint32_t stale_time = now.tv_sec - most_recent_end;
                //printf("Stale time = %d seconds \n", stale_time);

                uint32_t duration = most_recent_end - most_recent_start;
                if(duration < duration_sec) continue;

                if(stale_time > stale_limit_sec) continue;
                
                ++total_valid;
	}
        return (total_valid >= quorum_size);
}
