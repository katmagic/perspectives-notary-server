
/*
void set_consistent_length(server_list *server, Key* host_key) {

	server->contains_inconsistency = FALSE; // default

	// match is set to the ssh_result_list struct
	// that has the same key (type and value) as the
	// key passed into the function
	ssh_result_list *match = NULL;
	ssh_result_list *result;
	struct list_head *inner_pos;
	list_for_each(inner_pos,&(server->probe_results.list)) {
		result = list_entry(inner_pos, 	
			ssh_result_list, list);
		Key* probe_key = result->key;

		if(probe_key->type != host_key->type) 
			continue; // ignore keys of different types

       		if(!key_equal(probe_key,host_key)) {
			// type is same, but key is different.  Inconsistent!
			server->contains_inconsistency = TRUE;
		}
				
		if(match != NULL) {
			DPRINTF(DEBUG_ERROR, 
			"Error, more than one message received"
			" for a single dns-name, key pair \n");
			continue; // ok, for now
		}
		match = result;
	}
		
	if(match == NULL) {
		server->consistent_length = 0;
		return; 
	}
	int oldest_no_conflict = match->timestamps[0];
 
	list_for_each(inner_pos,&(server->probe_results.list)) {
		result = list_entry(inner_pos, 	
			ssh_result_list, list);
		if(result == match) continue;
		
		int index = result->num_probes - 1;
		int most_recent = result->timestamps[index];
				
		// test if a conflicting key has been seen
		// by this server since it first saw the good
		// key.  If so, find if there's a observation
		// of the same key more recently
		if(most_recent >= oldest_no_conflict) { 
			int i;
			// goes from oldest to newest
			oldest_no_conflict = 0;
			for(i = 0; i < match->num_probes; i++) {
				if(match->timestamps[i] < most_recent){
					oldest_no_conflict = match->timestamps[i];
					break;
				}
			}
		}
	}
	
	server->consistent_length = oldest_no_conflict;	

}
*/

// find the most recent key seen by any server that has the 
// same type as the host key, but different content
int getMostRecentConflict(SSHNotary *notary, Key* host_key) {
	int most_recent_conflict = -1;

	struct list_head *outer_pos, *inner_pos;
	server_list *server;
	list_for_each(outer_pos,&notary->probe_servers.list){
		server = list_entry(outer_pos, server_list, list);
		ssh_result_list *result;
		list_for_each(inner_pos,&(server->probe_results.list)) {
			result = list_entry(inner_pos, ssh_result_list, list);
			Key* probe_key = result->key;

			if(probe_key->type != host_key->type) 
				continue; // ignore keys of different types
			if(key_equal(probe_key, host_key))
				continue; // ignore keys that match host_key

			int last_saw_key = 
				result->timestamps[result->num_probes - 1];
			
			if(most_recent_conflict < last_saw_key){
				most_recent_conflict = last_saw_key;
			}
				
		}

	}
	return most_recent_conflict;
}

// returns the first timestamp of when any probe server 
// saw a key that matches 'host_key'
int getOldestCorrectSighting(SSHNotary *notary, Key* host_key) {
	int oldest_correct = -1;

	struct list_head *outer_pos, *inner_pos;
	server_list *server;
	list_for_each(outer_pos,&notary->probe_servers.list){
		server = list_entry(outer_pos, server_list, list);
		ssh_result_list *result;
		list_for_each(inner_pos,&(server->probe_results.list)) {
			result = list_entry(inner_pos, ssh_result_list, list);
			Key* probe_key = result->key;

			if(key_equal(probe_key, host_key)){

				int first_saw_key = result->timestamps[0];
				if(oldest_correct == -1 ||
					oldest_correct > first_saw_key){
					oldest_correct = first_saw_key;
				}
				
			}
		}

	}
	return oldest_correct;
}

// for each server, it finds the 'freshest' probe timestamp
// from that server, and then tells you the least fresh of
// each of these timestamps
int getMostStaleProbe(SSHNotary *notary) {
	int most_stale = -1;

	struct list_head *outer_pos, *inner_pos;
	server_list *server;
	list_for_each(outer_pos,&notary->probe_servers.list){
		server = list_entry(outer_pos, server_list, list);
		ssh_result_list *result;
			
		int last_probe = -1;
		list_for_each(inner_pos,&(server->probe_results.list)) {
			result = list_entry(inner_pos, ssh_result_list, list);
				
			int last_probe_for_key = 
				result->timestamps[result->num_probes - 1];
			if(last_probe_for_key > last_probe ||
				last_probe == -1) 
				last_probe = last_probe_for_key;
		}
		if(most_stale == -1){ 
			most_stale = last_probe;
		} else if(last_probe != -1 && last_probe < most_stale){
			most_stale = last_probe;
		}

	}
	return most_stale;
}

/*
// TODO: send IP address too?  
void check_key_consistency(SSHNotary *notary, Key* host_key, int* consistency_len,
		BOOL* sawInconsistency) {

	server_list *server;
	*sawInconsistency = FALSE; // by default, no inconsistencies

	int min_consistent_len = -1;
	struct list_head *outer_pos;
	list_for_each(outer_pos,&notary->probe_servers.list){
		server = list_entry(outer_pos, server_list, list);
		set_consistent_length(server, host_key);

		if(min_consistent_len == -1){
			min_consistent_len = server->consistent_length;
		} else {
			min_consistent_len = min(min_consistent_len,
						server->consistent_length);
		}
		if(server->contains_inconsistency)
			*sawInconsistency = TRUE;
	}
	*consistency_len = min_consistent_len;
}
*/
