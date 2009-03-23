//var url = "https://www.networknotary.org/get_xml.php?"
var url = "http://localhost:15217/?" 


function d_print(line) {
        dump(line);
        try {
           Firebug.Console.log(line);
        } catch(e) {
           /* ignore, this will blow up if Firebug is not installed */
        }
}

// this is the public key from keys/public.pem, which is needed to validate
// entries in the example database that is in SVN (or anything else you've
// created with keys/private.pem 

var public_key = "MIHKMA0GCSqGSIb3DQEBAQUAA4G4ADCBtAKBrAE0Ow4voLFzfAYf6PIVCT8CBz7Gts4/zWtAntmqk2CkvRw7KJJD9oB2RFjAVIhOIxSZN0GtLb4SjIMtDretJLIyd//UXx0lvOY8b8tc0XxpCnrMI6GPkmZ1oFZ2K9KSv7Fcega7fBsBvRuSZ1JsrdhW8xtCa1H7YqP9wnh4DYPssYhiNi/e9hbOHP3+spXxTyeTmJW6Xep8sd4j0pNdsQuV9SNd8Lv36+hkNEUCAwEAAQ==";

function query(){

    var curi = gBrowser.currentURI;
    var port = curi.port;

    if (port < 0){
        port = 443;
    }
    var service_id = curi.host + ":" + port + ",2"; 
    var resp = url + "host=" + curi.host + "&port=" + port + "&service_type=2&";
    d_print("query for: " + resp);
    d_print("service id = " + service_id);  
    var req  = XMLHttpRequest();
    req.open("GET", resp, true);
    
    /* Call back will execute when XmlHttpRequest has finished */
    req.onreadystatechange = 
        function (aEvt) {  
            if (req.readyState == 4) {  
                if(req.status == 200){
		   try { 
		    d_print(req.responseText); 
    		    var server_node = req.responseXML.documentElement;
                    var server_result = parse_server_node(server_node);
		    var bin_result = pack_result_as_binary(server_result,
							    service_id);
		    d_print(resultToString(server_result)); 
   		    var verifier = Cc["@mozilla.org/security/datasignatureverifier;1"].createInstance(Ci.nsIDataSignatureVerifier);
		    var sig = server_result.signature; 		  
		    var result = verifier.verifyData(bin_result, 
					sig, public_key);
                    d_print("result = " + result);
                  } catch (e) { 
			alert(e); 
		  } 
                }
                else {
                    dump("Error loading page\n");  
                }
            }  
        };  
    req.send(null);
}

