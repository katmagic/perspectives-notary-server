

// convert an xml '<server>' node to a javascript object
// In JSON synatax, this object has the following format: 
/* { "signature" : "XXXX", 
     "obs" : [  { "key" : "XXX", 
 		  "timestamps" : [ { "start" : XXX, "end" : YYY } ]
		} 
	     ] 
   }
*/  
function parse_server_node(server) { 

        if(server.nodeName != "server"){
            return null;
        }
        
        var res = new Object();
        res.obs     = new Array();
        for (var j = 0; j < server.childNodes.length; j++){
            var servchild = server.childNodes[j];

            if (servchild.nodeName == "sig"){
		var sig_base64 = servchild.firstChild.nodeValue;
                res.signature = add_der_signature_header(sig_base64); 
                continue;
            }

            if (servchild.nodeName != "result"){
                continue; 
            }

	    // new result
            var key_info = new Object(); 
            key_info.timestamps = new Array();
            for (var k = 0; k < servchild.childNodes.length; k++){
                var reschild = servchild.childNodes[k];

                if (reschild.nodeName == "key"){
		    key_info.key = reschild.firstChild.nodeValue;
                }

                if (reschild.nodeName != "timestamp"){
                    continue;
                }

		var ts; 
                for (var l = 0; l < reschild.childNodes.length; l++){
                    var timestamp = reschild.childNodes[l];
												    //FIXME: assumes ordering of start/end nodes
                    if (timestamp.nodeName == "start"){							ts = new Object(); 
                        ts.start = timestamp.firstChild.nodeValue.trim();
                    }

                    if (timestamp.nodeName == "end"){
                        ts.end = timestamp.firstChild.nodeValue.trim();
			key_info.timestamps.push(ts);
                    }
                }
            }
	    res.obs.push(key_info); 
        }
	return res; 
}

// Mozilla's verification API assumes a DER header describing the signature's
// cryptographic parameters.  The openssl-generated signatures returned by
// the notary server do not have this.  Since the header is the same for
// all notary responses, we just statically prepend the data here, and 
// re-encode the signature in base64.  
// see firefox-v2/xp_src/moz_crypto.cpp for details of header format
function add_der_signature_header(sig_base64) { 

  var base_str = Base64.decode(sig_base64); 
  var der_header_md5 = [ "0x30", "0x81", "0xbf", "0x30", "0x0d", "0x06", "0x09",
        "0x2a", "0x86", "0x48", "0x86", "0xf7", "0x0d", "0x01", "0x01", "0x04",
	 "0x05", "0x00", "0x03", "0x81", "0xad", "0x00"];
  var header_str = '';
  for (i = 0; i < der_header_md5.length; i++) { 
	header_str += String.fromCharCode(parseInt(der_header_md5[i],16));  	
  }
  return Base64.encode(header_str + base_str) ; 
} 


// Dumps all data in a server response to a string for easy debugging
function resultToString(server_result,show_sig){
	var out = ""; 
        for(var j = 0; j < server_result.obs.length; j++) { 
	    var o = server_result.obs[j]; 
            out += "ssl key: " + o.key + "'\n";
            for(var k = 0; k < o.timestamps.length; k++){
		var start_t = o.timestamps[k].start; 
		var end_t = o.timestamps[k].end; 
		var start_d = new Date(1000 * start_t).toDateString();  
		var end_d = new Date(1000 * end_t).toDateString();  
                out += "start:\t" + start_t + " - " + start_d + "\n"; 
                out += "end:  \t" + end_t + " - " + end_d + "\n"; 
            }   
        }  
	if(show_sig)
		out += "\tsignature = '" + server_result.signature + "'\n";  
	return out;
} 

//Note: the signature is computed over data in 
// network byte order (big endian) so we should do
// the same. 
// each observation has:
// service-id (variable length, terminated with null-byte) 
// num_timespans (2-bytes)
// key_len_bytes (2-bytes, always has value of 16 for now
// key type (1-byte), always has a value of 3 for SSL 
// key data (length specified in key_len_bytes) 
// list of timespan start,end pairs  (length is 2 * 4 * num_timespans)
// FIXME: The different keys actually need to be in the same order as 
// they were on the server, in order to compute the signature correctly.
// The xml seems to be parsed in a consistent way, but I don't know if
// that is guarenteed to be the case.  
function pack_result_as_binary(server_res,service_id) { 
	var bin_str = service_id;
 	bin_str += String.fromCharCode(0); // NULL-terminate
	 
	for (i = server_res.obs.length - 1; i >= 0; i--) { 
		var o = server_res.obs[i];
		var num_timespans = o.timestamps.length; 
		bin_str += String.fromCharCode((num_timespans >> 8) & 255, 
																	num_timespans & 255); 
		bin_str += String.fromCharCode(0,16,3); // key length is 16, type 3
		var hex_array = o.key.split(":"); 
		for(k = 0; k < hex_array.length; k++) { 
			bin_str += String.fromCharCode((parseInt(hex_array[k],16))); 
		}
		for (j = 0; j < o.timestamps.length; j++) { 
			var t = o.timestamps[j]; 
			bin_str += String.fromCharCode((t.start >> 24) & 255, 
							(t.start >> 16) & 255, 
							(t.start >> 8) & 255, 
							t.start & 255);  
			bin_str += String.fromCharCode((t.end >> 24) & 255, 
							(t.end >> 16) & 255, 
                                                        (t.end >> 8) & 255, 
							t.end & 255);  
		}
	} 
	return bin_str; 
} 
