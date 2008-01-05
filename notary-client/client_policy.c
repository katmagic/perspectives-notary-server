#include "flex_queue.h"
#include "client_policy.h"

// NOTE: this quorum code isn't actually correct.  It calculates something
// stronger than quorum, since it looks at only the most recent timespan for
// each server (when in fact, quorum could be preserved by a less than most
// recent timespan).   

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


int uint_compare(const void *a, const void *b) {
  return *(uint32_t*)a - *(uint32_t*)b;
}

// returns a shallow copy of the key information with a timespan
// that matches the specified time.  'notary_obs' should be the list of
// all observations from a single notary server (that is, we assume timespans
// do not overlap)
ssh_key_info* find_key_at_time(ssh_key_info_list *notary_obs, uint32_t time) {
    
    // loop through each timespan, to find the one that includes
    // the specified time. 
    struct list_head *inner_pos;
    ssh_key_info_list *elem;
    list_for_each(inner_pos,&(notary_obs->list)) {
      elem = list_entry(inner_pos, ssh_key_info_list, list);
      ssh_key_info *info = elem->info;
      int *timespans = FIND_TIMESPANS(info);
      for(int i = 0; i < info->num_timespans * 2; i = i + 2) {
        uint32_t start = timespans[i];
        uint32_t end = timespans[i + 1];
        if(start > time && end < time) 
          return info; // no copy, just return pointer
      }
    }
    return NULL; 
}

// we want to find each timestamp when one of the notaries started seeing
// a key other than what they saw in the past.  
BOOL get_all_time_changes(SSHNotary *notary, flex_queue* time_changes) {
  
  struct list_head *outer_pos;
  BOOL is_empty = TRUE;
  server_list *server;
  list_for_each(outer_pos,&notary->notary_servers.list){
    server = list_entry(outer_pos, server_list, list);
    if(server->notary_results == NULL) {
      DPRINTF(DEBUG_ERROR, "results are null \n"); 
      continue;
    }

    // loop through each timespan, recording its start time if it
    // is the first timespan for that key, otherwise only its end time.  
    struct list_head *inner_pos;
    ssh_key_info_list *elem;

    list_for_each(inner_pos,&(server->notary_results->list)) {
      elem = list_entry(inner_pos, ssh_key_info_list, list);
      ssh_key_info *info = elem->info;
      BOOL is_first = TRUE;

      int *timespans = FIND_TIMESPANS(info); 
      int num_spans = ntohs(info->num_timespans); 

      for(int i = 0; i < num_spans * 2; i = i + 2) {
        uint32_t start = ntohl(timespans[i]);
        uint32_t end = ntohl(timespans[i + 1]);
        is_empty = FALSE;
        if(is_first) {
          is_first = FALSE;
          queue_pushback(time_changes, &start); 
        }
        queue_pushback(time_changes, &end); 
      }
    }

  }
  return !(is_empty); 
}

// for a given key, check whether it has quorum at this specific time.
// To do so, check what key each of the notaries report at this time,
// and see if at least 'quorum_size' of them saw the specified key
BOOL has_quorum_at_time(SSHNotary *notary, char *key_data, uint16_t key_len, 
    uint8_t key_type, int quorum_size, uint32_t time) {

  int total_valid = 0;

  struct list_head *outer_pos;
  server_list *server;
  list_for_each(outer_pos,&notary->notary_servers.list){
    server = list_entry(outer_pos, server_list, list);
    
    if(server->notary_results == NULL) {
      //printf("no results for server \n");
      continue;
    }
    ssh_key_info* cur_key = find_key_at_time(server->notary_results, time);

    if(cur_key == NULL) {
      DPRINTF(DEBUG_ERROR,"Failed to find a key at time %d \n", time);
      continue;
    }

    if(key_type != cur_key->key_type) continue;
    if(key_len != ntohs(cur_key->key_len_bytes)) continue;

    char *key_buf = (char*)(cur_key + 1);
    if(memcmp(key_data, key_buf, key_len)) continue;

    ++total_valid; 
  }
  DPRINTF(DEBUG_INFO,"QUORUM TEST: required = %d  received = %d \n", 
      quorum_size, total_valid); 
  return (quorum_size <= total_valid); 

}

uint32_t get_quorum_duration(SSHNotary *notary, char *key_data, uint16_t key_len, 
      uint8_t key_type, int quorum_size, uint32_t stale_limit_sec, int *status) {

        struct timeval now;
        gettimeofday(&now, NULL);
       
        flex_queue *time_changes = queue_init(20, sizeof(int)); 
        if(!get_all_time_changes(notary, time_changes))
        {
            *status = -1;
            return 0;
        }
        *status = 0;
        
        // TODO: if any notary has results that are older than
        // stale_time_secs, we should ignore it when trying
        // to achieve quorum 
        // that can be detected within get_all_times_changes,
        // and then checked in has_quorum_at_time 

        int size = queue_size(time_changes); 
        int i;
        queue_sort(time_changes, uint_compare); 
        uint32_t cur_time, oldest = 0; 
        for(i = 0; i < size; i++) {
            queue_peek(time_changes, i, &cur_time); 
            // all times are end-times except the first one
            if(i != 0)   
              oldest = cur_time; 

            if( ! has_quorum_at_time(notary,key_data,key_len,
                  key_type,quorum_size,cur_time + 1)) {
              DPRINTF(DEBUG_INFO, "quorum failed for time %d \n", cur_time + 1); 
              break;
            }
        }
        
        printf("now = %d  oldest = %d \n", (int) now.tv_sec, oldest); 
        int diff = now.tv_sec - oldest; 
        printf("diff = %d  hours = %f  days = %f \n",
            diff, SEC2HOUR(diff), SEC2DAY(diff)); 

        return diff; 

}

