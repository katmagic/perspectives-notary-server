var url = "https://www.networknotary.org/get_xml.php?"

function query(){
    var curi = gBrowser.currentURI;
    var port = curi.port;

    if (port < 0){
        port = 443;
    }

    var resp = url + "host=" + curi.host + "&port=" + port + "&service_type=2";
    var req  = XMLHttpRequest();
    req.open("GET", resp, true);
    
    /* Call back will execute when XmlHttpRequest has finished */
    req.onreadystatechange = 
        function (aEvt) {  
            if (req.readyState == 4) {  
                if(req.status == 200){
                    owin(resp + "\n\n" + req.responseText);
                    parsed = parseRequest(req.responseXML);
                    owin(toStringRequest(parsed));
                }
                else {
                    dump("Error loading page\n");  
                }
            }  
        };  
    req.send(null);
}

/* for testing purposes */
function toStringRequest(results){
    var out = "";
    for(var i = 0; i < results.length; i++) { 
        out += "server " + results[i].server + "\n";
        for(var j = 0; j < results[i].obs.length; j++) { 
                out += "\tkey " + results[i].obs[j].key + "\n";
            for(var k = 0; k < results[i].obs[j].timestamps.length; k++){ 
                out +=
                    "\ttimetamp\n" +
                    "\t\tstart " + 
                    results[i].obs[j].timestamps[k].start + "\n" +
                    "\t\tend " + 
                    results[i].obs[j].timestamps[k].end + "\n" +
                    "\tend_timetamp\n";
            }   
        }   
    }   
    return out;
} 

/* Should take the document which is the result of an XMLHttpRequest returns
 * an obect representing that request */
function parseRequest(dc){
    var servnodes = dc.documentElement.childNodes;
    var results = new Array();
    var ri = -1;
    for (var i = 0; i < servnodes.length; i++){
        var server = servnodes[i];

        if(server.nodeName != "server"){
            continue;
        }
        
        ri++;
        results[ri] = new Object();
        for (var j = 0; j < server.childNodes.length; j++){
            var servchild = server.childNodes[j];

            if (servchild.nodeName == "ip"){
                results[ri].server = servchild.firstChild.nodeValue;
                continue;
            }

            if (servchild.nodeName != "result"){
                continue;
            }

            var rj = 0;
            results[ri].obs     = new Array();
            for (var k = 0; k < servchild.childNodes.length; k++){
                var reschild = servchild.childNodes[k];

                if (reschild.nodeName == "key"){
                    results[ri].obs[rj] = new Object();
                    results[ri].obs[rj].key = reschild.firstChild.nodeValue;
                    var rk = 0;
                }

                if (reschild.nodeName != "timestamp"){
                    continue;
                }

                var rk = -1;
                results[ri].obs[rj].timestamps = new Array();
                results[ri].obs[rj].timestamps[rk] = new Object();
                for (var l = 0; l < reschild.childNodes.length; l++){
                    var timestamp = reschild.childNodes[l];
                    if (timestamp.nodeName == "start"){
                        rk++;
                        results[ri].obs[rj].timestamps[rk] = new Object();
                        results[ri].obs[rj].timestamps[rk].start = 
                            timestamp.firstChild.nodeValue;
                    }

                    if (timestamp.nodeName == "end"){
                        results[ri].obs[rj].timestamps[rk].end = 
                            timestamp.firstChild.nodeValue;
                    }
                }
            }
        }
    }
    return results;
}

function owin(text){
    window.openDialog("chrome://jscript_perspectives/content/info.xul", "",
            "", text);
}
