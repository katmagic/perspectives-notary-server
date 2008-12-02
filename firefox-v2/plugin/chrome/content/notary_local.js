function query_json_notary_proxy(offered_key, host,port,service_id) { 
  try {
			var url = "https://www.networknotary.org:444/get_json.php?" + 
									"host=" + encodeURIComponent(host) + "&port=" + port 
									+ "&service_type=" + service_id; 
      var request = new XMLHttpRequest();
      request.open("GET",url,true);
      request.onload = {
        handleEvent : 
						function(evt) {
									var notary_results = eval("(" + request.responseText + ")"); 
									if(notary_debug) console.log("response: ",notary_results);
									var qd = get_quorum_duration(offered_key, notary_results, 3, 5 * 24 * 360); 
									if(notary_debug) console.log("qd = " + qd); 
                }
        };
      request.onerror = {
        handleEvent : function(evt) {
                                alert("failed to retreive results");
                      }
        };

  request.send("");

  } catch (e) {
        alert("failure getting notary response: " + e);
  }
} 
