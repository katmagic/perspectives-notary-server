function sort_number_list_desc(list){ 
	function sortNumber(a,b){ return b - a; }
	list.sort(sortNumber); 
} 


function find_key_at_time(server_results,desired_time) { 
 for(i = 0; i < server_results.obs.length; i++) { 
		var cur_obs = server_results.obs[i];
		//console.log("key: " + cur_obs.key); 
		for(j = 0; j < cur_obs.timestamps.length; j++) { 
			var test_end = cur_obs.timestamps[j].end;
			var test_start = cur_obs.timestamps[j].start;
			//console.log("start: " + test_start + " end: " + test_end); 
			if(desired_time >= test_start && desired_time <= test_end) { 
				return cur_obs.key;  
			}
		} 
 }
 return null; 
} 

function find_most_recent(server_results) { 
 var most_recent_time = 0; 
 for(var i = 0; i < server_results.obs.length; i++) { 
		var cur_obs = server_results.obs[i]; 
		for(var j = 0; j < cur_obs.timestamps.length; j++) { 
			var test_time = cur_obs.timestamps[j].end;
			if(test_time > most_recent_time) 
				most_recent_time = test_time; 
		} 
 }
 return most_recent_time; 
} 

function find_oldest_most_recent(results, stale_limit_secs,cur_time){
	var stale_limit = cur_time - stale_limit_secs; 
	var oldest_most_recent = cur_time + stale_limit_secs;
	for(var i = 0; i < results.length; i++) { 
		var most_recent = find_most_recent(results[i]);
		if(most_recent && (most_recent < oldest_most_recent)) { 
			if(most_recent > stale_limit) 
				oldest_most_recent = most_recent; 
		}
	}
	return oldest_most_recent; 
}


function get_num_valid_notaries(test_key,results,stale_limit_secs,cur_time){
	var stale_limit = cur_time - stale_limit_secs;
	var num_valid = 0; 
	for(var i = 0; i < results.length; i++) { 
			var mr_time = find_most_recent(results[i]); 
			if(mr_time == 0 || mr_time < stale_limit) 
				continue 
			var cur_key = find_key_at_time(results[i], mr_time); 
			if(cur_key == test_key) {
				//console.log("match for server: " + results[i].server); 
				num_valid++; 
			}
	}
	return num_valid; 
}

function get_all_key_changes(results) { 
	var change_set = {}; 
	for(var i = 0; i < results.length; i++) { 
		for(var j = 0; j < results[i].obs.length; j++) { 
			for(var k = 0; k < results[i].obs[j].timestamps.length; k++) { 
				var ts = results[i].obs[j].timestamps[k]; 
				change_set[ts.start] = ""; 
				change_set[ts.end] = ""; 
			}
		}
	}
  var change_list = []; 
	var x; 
	for (x in change_set) { 
		change_list.push(x); 
	}
	return change_list; 
} 

function check_current_consistency(test_key,results,quorum_size,stale_limit_secs,cur_time) {
  get_all_key_changes(results); 
	var num_valid = get_num_valid_notaries(test_key,results,stale_limit_secs,cur_time);
	if(notary_debug) console.log("cur_consistency: " + num_valid + " with q = " + quorum_size); 
	return num_valid >= quorum_size; 
}

function has_quorum_at_time(test_key, results, quorum_size, time) {
	//console.log("testing quorum for time " + time + " and key: " + test_key); 
	var total_valid = 0; 
	for(var i = 0; i < results.length; i++) { 
		if(results[i].obs.length == 0){ 
			//console.log(results[i].server + " has no results"); 
			continue; 
		}
		var cur_key = find_key_at_time(results[i],time); 
		if(cur_key == null) {
			//console.log(results[i].server + " has no key"); 
			continue; 
		}
		if(cur_key == test_key) {
			//console.log(results[i].server + " matched"); 
			total_valid++; 
		}else { 
			//console.log(results[i].server + " had different key: " + cur_key); 
		}
	}
	return total_valid >= quorum_size; 
} 



function get_quorum_duration(test_key, results, quorum_size, stale_limit_secs) { 
	var foo = new Date(); // Generic JS date object
	var unixtime_ms = foo.getTime(); // Returns milliseconds since the epoch
	var unixtime = parseInt(unixtime_ms / 1000);

	if(! check_current_consistency(test_key,results,quorum_size,stale_limit_secs,unixtime)) { 
		return -1; 
	}
	
	var oldest_most_recent = find_oldest_most_recent(results,unixtime,stale_limit_secs); 
	var nonzero_duration = false; 
  var time_changes = get_all_key_changes(results); 
	sort_number_list_desc(time_changes); 
	//console.log("sorted times: ", time_changes); 
  var test_time = unixtime; 
	for(var i = 0; i < time_changes.length; i++) {
		test_time = time_changes[i]; 
		if(time_changes[i] > oldest_most_recent) { 
			//console.log("skipping test_time = " + test_time); 
			continue; 
		}
		if(!has_quorum_at_time(test_key,results,quorum_size,test_time)) { 
			//console.log("quorum failed for time " + test_time); 
			break; 
		}
		nonzero_duration = true; 
	}
	var diff = unixtime - test_time + 1; 
	if(diff > 0 && nonzero_duration) 
		return diff;

	return 0; 
} 
 
