#include "flex_queue.h"
#include "client_policy.h"
#include "net_util.h"

// NOTE: this quorum code isn't actually correct.  It calculates something
// stronger than quorum, since it looks at only the most recent timespan for
// each server (when in fact, quorum could be preserved by a less than most
// recent timespan).   
// INSTEAD USE: get_quorum_duration 
/*
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
*/

int uint_compare(const void *a, const void *b) {
  return *(uint32_t*)b - *(uint32_t*)a;
}

// returns a shallow copy of the key information with a timespan
// that matches the specified time.  'notary_obs' should be the list of
// all observations from a single notary server (that is, we assume timespans
// do not overlap or even ''touch''
ssh_key_info* find_key_at_time(ssh_key_info_list *notary_obs, uint32_t time) {
    
    // loop through each timespan, to find the one that includes
    // the specified time. 
    struct list_head *inner_pos;
    ssh_key_info_list *elem;
    list_for_each(inner_pos,&(notary_obs->list)) {
      elem = list_entry(inner_pos, ssh_key_info_list, list);
      ssh_key_info *info = elem->info;
      int *timespans = FIND_TIMESPANS(info);
      int num_spans = ntohs(info->num_timespans); 
      for(int i = 0; i < num_spans * 2; i = i + 2) {
        uint32_t start = ntohl(timespans[i]);
        uint32_t end = ntohl(timespans[i + 1]);
        if(start <= time && end >= time) {
          //DPRINTF(DEBUG_POLICY, " %d is in span %d to %d \n", time, start, end); 
          return info; // no copy, just return pointer
        }
      }
    }
    return NULL; 
}


// we want to find each timestamp when one of the notaries started seeing
// a key other than what they saw in the past.  
// we actually return both starting and ending times, in case there are
// gaps between timespans 
void get_all_time_changes(SSHNotary *notary, flex_queue* time_changes) {
  
  struct list_head *outer_pos;
  server_list *server;
  list_for_each(outer_pos,&notary->notary_servers.list){
    server = list_entry(outer_pos, server_list, list);
    if(server->notary_results == NULL) {
      continue;
    }

    // loop through each timespan, recording its start time if it
    // is the first timespan for that key, otherwise only its end time.  
    struct list_head *inner_pos;
    ssh_key_info_list *elem;

    list_for_each(inner_pos,&(server->notary_results->list)) {
      elem = list_entry(inner_pos, ssh_key_info_list, list);
      ssh_key_info *info = elem->info;

      int *timespans = FIND_TIMESPANS(info); 
      int num_spans = ntohs(info->num_timespans); 

      // add two times for each timespan
      for(int i = 0; i < num_spans * 2; i = i + 2) {
        uint32_t before_start = ntohl(timespans[i]) - 1;
        uint32_t at_end = ntohl(timespans[i + 1]);
        queue_pushback(time_changes, &before_start); 
        queue_pushback(time_changes, &at_end); 
      }
    }

  }
}

BOOL test_key_match(ssh_key_info *test_key, 
                    char* key_data, uint16_t key_len, uint8_t key_type) {
  
    if(key_type != test_key->key_type) return FALSE;
    if(key_len != ntohs(test_key->key_len_bytes)) return FALSE;
    char *key_buf = (char*)(test_key + 1);
    if(memcmp(key_data, key_buf, key_len)) return FALSE;

    return TRUE; 
}

// finds the most recent 'end' timestamp for a server
// this represents the last successful probe by the server
// return value of 0 indicates that no result was found
uint32_t find_most_recent(server_list *server) {
    if(server->notary_results == NULL) {
      return 0;
    }

    struct list_head *inner_pos;
    ssh_key_info_list *elem;

    uint32_t most_recent = 0; // find the most recent probe from this server
    list_for_each(inner_pos,&(server->notary_results->list)) {
      elem = list_entry(inner_pos, ssh_key_info_list, list);
      ssh_key_info *info = elem->info;

      int *timespans = FIND_TIMESPANS(info); 
      int num_spans = ntohs(info->num_timespans); 

      for(int i = 0; i < num_spans * 2; i = i + 2) {
        uint32_t end = ntohl(timespans[i + 1]);
        //looking for most-recent (>) timespan end value 
        if(end > most_recent) 
          most_recent = end; 
      }
    } // end for-each key 
    return most_recent; 
}

// this function wins the award for the most confusing function name ever.
// What it does is look at the timestamp of each notary's most recent probe
// and returns the oldest such value, subject to the condition that the probe
// is not older than 'max_stale_time' seconds
uint32_t find_oldest_most_recent(SSHNotary *notary, 
                                  uint32_t cur_time, uint32_t max_stale_time) {
  
  uint32_t stale_limit = cur_time - max_stale_time; 
  uint32_t oldest_most_recent = cur_time; // default to current time 

  struct list_head *outer_pos;
  server_list *server;
  list_for_each(outer_pos,&notary->notary_servers.list){
    server = list_entry(outer_pos, server_list, list);

    uint32_t most_recent = find_most_recent(server); 

    // check if we found a most-recent timestamp for this key
    // and whether this is older (<) our existing oldest-most-recent
    if(most_recent && (most_recent < oldest_most_recent)) {
        //only record if it is more recent (>) than the stale limit
	if(most_recent >= stale_limit) {
        	oldest_most_recent = most_recent; 
      	}else {
		DPRINTF(DEBUG_POLICY,"Ignoring most recent time %d is older "
		"than stale limit  %d for server %s \n", most_recent, 
		stale_limit, ip_2_str(server->ip_addr)); 
	}
    }
  } // end for-each server 
  return oldest_most_recent; 
}


// determines if the latest key seen by each of the servers matches 
BOOL check_current_consistency(SSHNotary *notary, int quorum_size,  
                       uint32_t cur_time, uint32_t max_stale_time, 
                        char* key_data, uint16_t key_len, uint8_t key_type) {
  
  uint32_t stale_limit = cur_time - max_stale_time; 
  int num_valid = 0; 

  struct list_head *outer_pos;
  server_list *server;
  list_for_each(outer_pos,&notary->notary_servers.list){
    server = list_entry(outer_pos, server_list, list);

    uint32_t most_recent = find_most_recent(server); 
  
    if(most_recent == 0 || most_recent < stale_limit)
      continue; 

    ssh_key_info* cur_key = find_key_at_time(server->notary_results, most_recent);
    BOOL is_match = test_key_match(cur_key,key_data,key_len,key_type); 
    if(is_match) {
        DPRINTF(DEBUG_POLICY,"Most recent obs. by server %s:%d is a match \n", 
        ip_2_str(server->ip_addr), server->port);
        ++num_valid; // count toward quorum
    }
   
  } // end for-each server 

  return (num_valid >= quorum_size); 
}



// for a given key, check whether it has quorum at this specific time.
// To do so, check what key each of the notaries report at this time,
// and see if at least 'quorum_size' of them saw the specified key
BOOL has_quorum_at_time(SSHNotary *notary, char *key_data, uint16_t key_len, 
    uint8_t key_type, int quorum_size, uint32_t time) {

  int total_valid = 0;

  struct list_head *outer_pos;
  server_list *server;
  int server_index = 0;

  DPRINTF(DEBUG_POLICY, "BEGIN quorum Test for t = %d \n", time); 

  list_for_each(outer_pos,&notary->notary_servers.list){
    server = list_entry(outer_pos, server_list, list);
    ++server_index; 
    
    if(server->notary_results == NULL) {
      DPRINTF(DEBUG_POLICY,"Server %s:%d provided no results \n", 
          ip_2_str(server->ip_addr), server->port);
      continue;
    }
    ssh_key_info* cur_key = find_key_at_time(server->notary_results, time);

    if(cur_key == NULL) {
      DPRINTF(DEBUG_POLICY,"Server %s:%d has no key for this time\n", 
          ip_2_str(server->ip_addr), server->port);
      continue;
    }

    BOOL is_match = test_key_match(cur_key,key_data,key_len,key_type); 

    if(!is_match) {
      DPRINTF(DEBUG_POLICY,"Server %s:%d has different key \n", 
          ip_2_str(server->ip_addr), server->port);
      continue;
    }

    DPRINTF(DEBUG_POLICY,"Server %s:%d found key match \n", 
          ip_2_str(server->ip_addr), server->port);
    ++total_valid; 
  }
  DPRINTF(DEBUG_POLICY,"END quorum test: required = %d  received = %d \n", 
      quorum_size, total_valid); 
  return (total_valid >= quorum_size); 

}

// returns quorum duration in seconds
// if no keys are found, will return -1 in the status variable
// 'stale_limit_sec' is the max amount of time (in seconds) between now and a
// a notary's most recent probe that we will 'forgive' and not count the lack of a probe
// against quorum.  
uint32_t get_quorum_duration(SSHNotary *notary, char *key_data, uint16_t key_len, 
      uint8_t key_type, int quorum_size, uint32_t stale_limit_sec, BOOL *is_cur_consistent) {

        struct timeval now;
        gettimeofday(&now, NULL);


        BOOL consistent = check_current_consistency(notary, quorum_size, now.tv_sec, 
                    stale_limit_sec, key_data, key_len, key_type); 
        if(!consistent) {
          DPRINTF(DEBUG_POLICY, "Offered key is INCONSISTENT\n"); 
          *is_cur_consistent = FALSE;
          return 0; 
        }
        *is_cur_consistent = TRUE; 

        flex_queue *time_changes = queue_init(20, sizeof(int)); 
        get_all_time_changes(notary, time_changes); 
        
        uint32_t oldest_most_recent = find_oldest_most_recent(notary, 
                                              now.tv_sec, stale_limit_sec); 

        DPRINTF(DEBUG_POLICY, "Key is currently consistent: oldest_most_recent = %d "
                                    "(cur = %d) \n", oldest_most_recent, (uint32_t)now.tv_sec); 
        int size = queue_size(time_changes); 
        
        if(oldest_most_recent == (uint32_t)now.tv_sec) { 
          DPRINTF(DEBUG_ERROR, "ERROR:oldest-most-recent is stale, but keys are cur-consistent?? \n"); 
          return 0; 
        }

        BOOL nonzero_duration = FALSE; 
        int i;
        queue_sort(time_changes, uint_compare); 
        uint32_t test_time = now.tv_sec; 
        for(i = 0; i < size; i++) {
            queue_peek(time_changes, i, &test_time);

            // ignore any times that are more recent than 'oldest_most_recent'
            if(test_time > oldest_most_recent) { 
              DPRINTF(DEBUG_POLICY,"skipping test_time = %d \n", test_time); 
              continue; 
            }
              
            if( ! has_quorum_at_time(notary,key_data,key_len,
                  key_type,quorum_size, test_time)) {
              DPRINTF(DEBUG_POLICY, "QUORUM FAILED for time = %d \n", test_time); 
              break;
            }
            nonzero_duration = TRUE;// duration is > 0 
        }
       
        int diff = now.tv_sec - test_time + 1;
        if(diff > 0 && nonzero_duration)
          return diff;

        return 0; 

}

