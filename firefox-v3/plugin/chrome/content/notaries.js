var MY_ID = "perspectives@cmu.edu"; 
var TIMEOUT_SEC = 5; 

var STATE_IS_BROKEN   = 
  Components.interfaces.nsIWebProgressListener.STATE_IS_BROKEN;
var STATE_IS_INSECURE = 
  Components.interfaces.nsIWebProgressListener.STATE_IS_INSECURE;
var STATE_IS_SECURE = 
  Components.interfaces.nsIWebProgressListener.STATE_IS_SECURE;

var strbundle = null; // this isn't loaded when things are intialized

var nonrouted_ips = [ "^192\.168\.", "^10.", "^172\.1[6-9]\.", 
			"^172\.2[0-9]\.", "172\.3[0-1]\.", "^169\.254\.", 
			"^127\.0\.0\.1$"]; // could add many more
var notary_debug = true;

// holds query reply data until all requests for a particular
// service_id have either completed or timed-out.  
// The key for this data is the service_id string.  
// The data is a list of 'notary data' objects.  The object will be
// empty in the case of an invalid signature or timeout
var query_result_data = {}; 
var query_timeoutid_data = {}; 
// list of objects representing each notary server's name + port and public key.
// this list is populated by init_notarylist() 
var notaries = []; 

 
function is_nonrouted_ip(ip_str) { 
	for each (regex in nonrouted_ips) { 
		if(ip_str.match(RegExp(regex))) { 
			return true; 
		}
	} 
	return false; 
} 

function getdns() {
	var cls = Components.classes['@mozilla.org/network/dns-service;1'];
        var iface = Components.interfaces.nsIDNSService;
        return cls.getService(iface);
}

var dns = getdns(); 

// it is likely that all IPs are reachable, or none are,
// but we are conservative and continue even if a single 
// IP seems routable
function host_is_unreachable(hostname) {  
  var ip_str = "";
  var ips = Array();  
  var nsrecord = dns.resolve(hostname,true); 
  while (nsrecord && nsrecord.hasMore()) 
	ips[ips.length] = nsrecord.getNextAddrAsString(); 
  for each (ip_str in ips) { 
  	if(!is_nonrouted_ip(ip_str)) { 
		return null; 
	}
	d_print("main", "unreachable ip = " + ip_str + "\n");  
  }
  return ips; 
} 

/* Data */
var whitelist     = new Array();
var ssl_cache     = new Object();
var root_prefs    = Components.classes["@mozilla.org/preferences-service;1"]
  .getService(Components.interfaces.nsIPrefBranchInternal);
var overrideService = 
  Components.classes["@mozilla.org/security/certoverride;1"]
  .getService(Components.interfaces.nsICertOverrideService);
var broken = false;

// flag to make sure we only show component load failed alert once
// per firefox session.  Otherwise, the user gets flooded with it.  
var show_component_failed = true; 

// if the tab changes to a webpage that has no notary
// results, set the 'reason' property of this object to explain why.  
// I use this hack b/c ssl_cache only caches info for sites we have
// probed, wherease we want to communicate info to the status pop-up
// about sites we haven't probed. 
var tab_info_cache = {}; 
var other_cache = {}; 
other_cache["debug"] = ""; 

function clear_cache(){
  ssl_cache = new Object();
}

//Sets the tooltip and the text of the favicon popup on https sites
function setFaviconText(str){
  document.getElementById("identity-box").tooltipText = str;
}

function getFaviconText(){
  return document.getElementById("identity-box").tooltipText;
}

function clear_existing_banner(b, value_text) { 
  try { 
    //Happens on requeryAllTabs

    try{
      var notificationBox = b.getNotificationBox();
    }
    catch(e){
      return;
    }
  	var oldNotification = 
    	notificationBox.getNotificationWithValue(value_text);
  	if(oldNotification != null)
    		notificationBox.removeNotification(oldNotification);
 	} catch (err) { 
		d_print("error","clear_existing_banner error: " + err); 	
   	} 
} 

function notifyOverride(b){
  //Happens on requeryAllTabs

  try{
    var notificationBox = b.getNotificationBox();
  }
  catch(e){
    return;
  }
  var notificationBox = b.getNotificationBox();
  clear_existing_banner(b, "Perspectives"); 

  var priority = notificationBox.PRIORITY_INFO_LOW;
  var message = strbundle.getString("verificationSuccess");  
  var buttons = [{
    accessKey : "", 
    label: strbundle.getString("learnMore"), 
    accessKey : "", 
    callback: function() {
      b.loadOneTab(
      "chrome://perspectives/locale/help.html", null, null,
      null, false);
    }
  }];
    
  notificationBox.appendNotification(message, "Perspectives", null,
    priority, buttons);
}

function notifyFailed(b){

  //Happens on requeryAllTabs

  try{
    var notificationBox = b.getNotificationBox();
  }
  catch(e){
    return;
  }
  var notificationBox = b.getNotificationBox();

  clear_existing_banner(b, "Perspectives"); 

  var priority = notificationBox.PRIORITY_CRITICAL_LOW;
  var message = strbundle.getString("unableToVerify");  
  var buttons = null;
  /* Uncomment when we have some sort of system
  var buttons = [{
    label: strbundle.getString("reportThis"), 
    accessKey : "", 
    callback: function() {
      alert("Do Stuff");
    }
  }];
  */
  notificationBox.appendNotification(message, "Perspectives", null,
    priority, buttons);
}

// this is the drop down which is shown if preferences indicate
// that notaries should only be queried with user permission
function notifyNeedsPermission(b){

  //Happens on requeryAllTabs 
  try{
    var notificationBox = b.getNotificationBox();
  }
  catch(e){
    return;
  }

  clear_existing_banner(b, "Perspectives-Permission"); 
  var priority = notificationBox.PRIORITY_WARNING_HIGH;
  var message = strbundle.getString("needsPermission");  
  var buttons = null;
  var buttons = [
    {
    label: strbundle.getString("yesContactNotaries"), 
    accessKey : "", 
    callback: function() {
      try { 


        //Happens on requeryAllTabs
        try{
          var notificationBox = b.getNotificationBox();
        }
        catch(e){
          return;
        }

        var nbox = b.getNotificationBox();
        nbox.removeCurrentNotification();
      } 
      catch (err) {
        // sometimes, this doesn't work.  why?
        // well, we'll just have to remove them all
        try { 
          nbox.removeAllNotifications();
          d_print("main", "successfully removed all notifications\n");  
        } 
        catch (err2) { 
          d_print("error","probe_permission error2:" + err2 + "\n"); 
        } 
        d_print("error","probe_permission error1: " + err + "\n"); 
      } 
      // run probe
      d_print("main", "User gives probe permission\n"); 
      var uri = b.currentURI;
      updateStatus(b,true); 
    }},
    { 
    label: strbundle.getString("learnMore"),
    accessKey : "", 
    callback: function() {
      b.loadOneTab(
      "chrome://perspectives/locale/help.html", null, null,
      null, false);
    } 
  }];
  notificationBox.appendNotification(message, "Perspectives-Permission", null,
    priority, buttons);
}

// this is the drop down which is shown if the repsonse
// receive no notary replies.  
function notifyNoReplies(b){

  //Happens on requeryAllTabs 
  try{
    var notificationBox = b.getNotificationBox();
  }
  catch(e){
    return;
  }

  clear_existing_banner(b, "Perspectives-Permission"); 
  clear_existing_banner(b, "Perspectives"); 
  var priority = notificationBox.PRIORITY_CRITICAL_LOW;
  var message = strbundle.getString("noRepliesReceived");  
  var buttons = null;
  var buttons = [
    { 
    label: strbundle.getString("firewallHelp"),
    accessKey : "", 
    callback: function() {
      b.loadOneTab(
      "chrome://perspectives_main/content/firewall.html", null, null,
      null, false);
    } 
  }];
  notificationBox.appendNotification(message, "Perspectives", null,
    priority, buttons);
}

//certificate used in caching
function SslCert(host, port, md5, summary, tooltip, svg, duration, secure){
  this.host     = host;
  this.port     = port;
  this.md5      = md5;
  this.secure   = secure;
  this.duration = duration;
  this.summary  = summary;
  this.tooltip  = tooltip;
  this.svg      = svg;
}

function onWhitelist(host){
  var length = whitelist.length //heard a rumor that this is O(n) sometimes
  for(var i = 0; i < length; i++){
    if(whitelist[i] == ""){//don't know why i need this
      continue;
    }
    if(host.indexOf(whitelist[i]) >= 0){
      d_print("main","whitelist match: " + whitelist[i] + "\n");
      return true;
    }
  }
  return false;
}

function get_invalid_cert_SSLStatus(uri){
  var recentCertsSvc = 
    Components.classes["@mozilla.org/security/recentbadcerts;1"]
    .getService(Components.interfaces.nsIRecentBadCertsService);
  if (!recentCertsSvc)
    return null;

  var port = uri.port; 
  if(port == -1) 
    port = 443; 

  var hostWithPort = uri.host + ":" + port;
  var gSSLStatus = recentCertsSvc.getRecentBadCert(hostWithPort);
  if (!gSSLStatus)
    return null;
  return gSSLStatus;
}

function cert_from_SSLStatus(gSSLStatus){
  return gSSLStatus.QueryInterface(Components.interfaces.nsISSLStatus)
    .serverCert;
}

// gets current certificat, if it FAILED the security check 
function psv_get_invalid_cert(uri) { 
  var gSSLStatus = get_invalid_cert_SSLStatus(uri);
  if(!gSSLStatus){
    return null;
  }
  return cert_from_SSLStatus(gSSLStatus);
} 

// gets current certificate, if it PASSED the browser check 
function psv_get_valid_cert(ui) { 
  try { 
    ui.QueryInterface(Components.interfaces.nsISSLStatusProvider); 
    if(!ui.SSLStatus) 
      return null; 
    return ui.SSLStatus.serverCert; 
  }
  catch (e) {
    d_print("error", "Perspectives Error: " + e); 
    return null;
  }
} 

function getCertificate(browser){
  var uri = browser.currentURI;
  var ui  = browser.securityUI;
  var cert = psv_get_valid_cert(ui);
  if(!cert){
    cert = psv_get_invalid_cert(uri);  
  }

  if(!cert) {
    return null;
  }
  return cert;
}


function queryNotaries(cert, uri,browser,has_user_permission){

  if(!cert) { 
    d_print("error","No certificate found for: " + uri.host); 
    return null; 
  } 

  var port = uri.port; 
  if(port == -1) 
    port = 443; 
  var service_id = uri.host + ":" + port + ",2"; 
  // send a request to each notary

  if(query_result_data[service_id] != null) { 
	d_print("main", "already querying '" + service_id + "'.  Do not requery"); 
	return; 
  }

  query_result_data[service_id] = [];  
  for(i = 0; i < notaries.length; i++) { 
    var notary_server = notaries[i]; 
    var full_url = "http://" + notary_server.host + 
	"?host=" + uri.host + "&port=" + port + "&service_type=2&";
    d_print("query", "sending query: '" + full_url + "'");
    var req  = XMLHttpRequest();
    req.open("GET", full_url, true);

    //NOTE: ugly, but we need to create a closure here, otherwise
    // the callback will only see the values for the final server
    req.onreadystatechange = (function(r,ns) { 
		return function(evt) { 
			notaryAjaxCallback(uri,cert, r, ns,service_id,
				browser,has_user_permission); 
    		}
    })(req,notary_server);  
    req.send(null);
  }
    
  query_timeoutid_data[service_id] = window.setTimeout(function () { 
		d_print("main", "timeout for " + service_id); 
		notaryQueriesComplete(uri,cert,service_id,browser,
					has_user_permission, 
					query_result_data[service_id]);
		delete query_result_data[service_id]; 
		delete query_timeoutid_data[service_id];  
	}, 
	TIMEOUT_SEC * 1000 
    ); 

} 
        
function notaryAjaxCallback(uri, cert, req, notary_server,service_id,
				browser,has_user_permission) {  
	
   if (req.readyState == 4) {  
   	if(req.status == 200){
	    try { 
		 
		 d_print("query", req.responseText); 
    		 var server_node = req.responseXML.documentElement;
                 var server_result = parse_server_node(server_node,1);
		 var bin_result = pack_result_as_binary(server_result,
							    service_id);
		 d_print("query", resultToString(server_result,false)); 
   		 var verifier = Cc["@mozilla.org/security/datasignatureverifier;1"].createInstance(Ci.nsIDataSignatureVerifier);
		 var sig = server_result.signature; 		  
		 var result = verifier.verifyData(bin_result, 
				server_result.signature, notary_server.public_key);
		 if(!result) { 
			d_print("error", "Invalid signature from : " + 
							notary_server.host); 
			return; 
		 }
		 server_result.server = notary_server.host; 
               	 if(query_result_data[service_id] == null) { 
			d_print("query","Query reply for '" + service_id + 
				"' has no query result data"); 
			return; 
		 } 
		 d_print("query","adding result from: " + notary_server.host); 
		 query_result_data[service_id].push(server_result); 
 
		 var num_replies = query_result_data[service_id].length; 
		 if(num_replies == notaries.length) { 
			d_print("query","got all server replies"); 	
			notaryQueriesComplete(uri,cert,service_id,browser,
						has_user_permission, 
						query_result_data[service_id]);
			delete query_result_data[service_id];
			window.clearTimeout(query_timeoutid_data[service_id]);
			delete query_timeoutid_data[service_id];  
		  } 
                } catch (e) { 
			d_print("error", "exception: " + e); 
		} 
             } else { // HTTP ERROR CODE
                    d_print("error", "HTTP Error code when querying notary");  
             }
      }  
}  

function notaryQueriesComplete(uri,cert,service_id,browser,has_user_permission,
				server_result_list) {
  try {
    var test_key = cert.md5Fingerprint.toLowerCase();
    var max_stale_sec = 2 * 24 * 3600; // 2 days (FIXME: make this a pref)
    var q_thresh = root_prefs.getIntPref("perspectives.quorum_thresh") / 100;
    var q_required = Math.round(notaries.length * q_thresh); 
    var unixtime = get_unix_time(); 
    var quorum_duration = get_quorum_duration(test_key, server_result_list, 
					q_required, max_stale_sec,unixtime);  
    var is_consistent = quorum_duration != -1;
 
    var qd_days =  Math.round((quorum_duration / (3600 * 24)) * 1000) / 1000;
    var obs_text = ""; 
    for(var i = 0; i < server_result_list.length; i++) {
	obs_text += "\nNotary: " + server_result_list[i].server + "\n";  
	obs_text += resultToString(server_result_list[i]); 
    }  
    var qd_str = (is_consistent) ? qd_days + " days" : "none";
    var str = "Notary Lookup for: " + service_id + "\n";
    			str += "Key = " + cert.md5Fingerprint + "\n"; 
    			str += "Results:\n"; 
    			str += "Quorum duration: " + qd_str + "\n"; 
    			str += "Notary Observations: \n" + obs_text + "\n"; 
    d_print("main","\n" + str + "\n");
    var svg = get_svg_graph(service_id, server_result_list, 30);
    d_print("main", svg);  
    ssl_cache[uri.host] = new SslCert(uri.host, uri.port,cert.md5Fingerprint, 
		str, null,svg, qd_days, is_consistent);
    process_notary_results(uri,browser,has_user_permission); 

   } catch (e) { 
     alert(e); 
   } 
}

  
/* There is a bug here.  Sometimes it gets into a browser reload 
 * loop.  Come back to this later */

function do_override(browser, cert,isTemp) { 
  var uri = browser.currentURI;
  d_print("main", "Do Override\n");

  gSSLStatus = get_invalid_cert_SSLStatus(uri);
  var flags = 0;
  if(gSSLStatus.isUntrusted)
    flags |= overrideService.ERROR_UNTRUSTED;
  if(gSSLStatus.isDomainMismatch)
    flags |= overrideService.ERROR_MISMATCH;
  if(gSSLStatus.isNotValidAtThisTime)
    flags |= overrideService.ERROR_TIME;

  overrideService.rememberValidityOverride(
			uri.asciiHost, uri.port, cert, flags, isTemp);

  setTimeout(function (){ 
    browser.loadURIWithFlags(uri.spec, flags);}, 25);
  return true;
}



/* Updates the status of the current page */
//Make this a bit more efficient when I get a chance
// 'has_user_permission' indicates whether the user
// explicitly pressed a button to launch this query,
// by default this is not the case
function updateStatus(browser, has_user_permission){

  if(strbundle == null) 
     strbundle = document.getElementById("notary_strings");

  d_print("main", "Update Status\n");
  if(!browser){
    d_print("error","No Browser!!\n");
    return;
  }
  var uri = browser.currentURI;
  if(!uri) { 
    var text = strbundle.getString("noDataError"); 
    setStatus(STATE_NEUT,text); 
    other_cache["reason"] = text;
    return;
  } 
  if(!uri.host){
    return;
  }
  var ti = tab_info_cache[uri.spec]; 
  if(!ti) { 
    ti = {}; 
    tab_info_cache[uri.spec] = ti; 
  }
  
  d_print("main", "Update Status: " + uri.spec + "\n");

  if(uri.scheme != "https"){
    var text = strbundle.getFormattedString("nonHTTPSError", [ uri.host, uri.scheme ]);
    setStatus(STATE_NEUT,text); 
    other_cache["reason"] = text;
    return;
  } 
  if(onWhitelist(uri.host)){
    var text = strbundle.getFormattedString("whitelistError", [uri.host] ); 
    setStatus(STATE_NEUT,text); 
    other_cache["reason"] = text; 
    return;
  }
  var unreachable = host_is_unreachable(uri.host); 
  if(unreachable) { 
    var text = strbundle.getFormattedString("rfc1918Error", [ uri.host ])
    setStatus(STATE_NEUT,text); 
    other_cache["reason"] = text; 
    return;
  } 

  ti.broken         = false;
  ti.cert       = getCertificate(browser);
  if(!ti.cert){
    var text = strbundle.getFormattedString("noCertError", [ uri.host ])
    setStatus(STATE_NEUT,text); 
    other_cache["reason"] = text; 
    return;
  }
  var md5        = ti.cert.md5Fingerprint;
  var state      = browser.securityUI.state;
  var gSSLStatus = null;

  ti.is_override_cert = overrideService.isCertUsedForOverrides(ti.cert, true, true);
  d_print("main", "is_override_cert = " + ti.is_override_cert + "\n"); 
  var check_good = root_prefs.getBoolPref("perspectives.check_good_certificates"); 

  if(state & STATE_IS_SECURE) { 
    d_print("main", "clearing any existing permission banners\n"); 
    clear_existing_banner(browser, "Perspecives-Permission"); 
  }

  // see if the browser has this cert installed prior to this browser session
  ti.already_trusted = (state & STATE_IS_SECURE) && 
    !(ti.is_override_cert && ssl_cache[uri.host]); 
  if(!check_good && ti.already_trusted) {
    var text = strbundle.getString("noProbeRequestedError"); 
    setStatus(STATE_NEUT,text); 
    other_cache["reason"] = text; 
    return;
  } 

  if(!ti.is_override_cert && state & STATE_IS_INSECURE){
    d_print("main","state is STATE_IS_INSECURE, we need an override\n");
    ti.broken = true; 
  }

  //Update ssl cache cert
  ti.firstLook = false;
  if(!ssl_cache[uri.host] || ssl_cache[uri.host].md5 != md5){
    ti.firstLook = true;
    d_print("main", uri.host + " needs a request\n"); 
    var needs_perm = root_prefs.getBoolPref("perspectives.require_user_permission"); 
    if(needs_perm && !has_user_permission) {
      d_print("main", "needs user permission\n");  
      notifyNeedsPermission(browser);
      var text = strbundle.getString("needsPermission"); 
      setStatus(STATE_NEUT,text); 
      other_cache["reason"] = text;  
      return; 
    } 
    d_print("main", "Contacting notaries\n"); 
    // this call is asynchronous.  after hearing from the 
    // notaries, the logic picks up again with the function 
    // 'done_querying_notaries()' below
    queryNotaries(ti.cert, uri,browser,has_user_permission);
  }else {
    process_notary_results(uri,browser,has_user_permission); 
  }
}


function process_notary_results(uri,browser,has_user_permission) {  
  try { 
 
  var ti = tab_info_cache[uri.spec]; 
  ti.notary_valid = false; // default 
  cache_cert = ssl_cache[uri.host];
  if( !ti.broken && 
      !cache_cert.identityText &&
      getFaviconText().indexOf("Perspectives") < 0){
    cache_cert.identityText = 
    setFaviconText(getFaviconText() + "\n\n" + 
    "Perspectives has validated this site");
  }
  var required_duration   = 
    root_prefs.getIntPref("perspectives.required_duration") / 100.0;

  if (cache_cert.summary.indexOf("ssl key") == -1) { 
    	cache_cert.tooltip = strbundle.getString("noRepliesWarning");
    	setStatus(STATE_NSEC, cache_cert.tooltip);
	if(ti.broken) { 
	  notifyNoReplies(browser); 
	} 
  } else if(!cache_cert.secure){
    cache_cert.tooltip = strbundle.getString("inconsistentWarning");
    setStatus(STATE_NSEC, cache_cert.tooltip);
    if(ti.broken && ti.firstLook){
      notifyFailed(browser);
    }
  } else if(cache_cert.duration < required_duration){
    cache_cert.tooltip = strbundle.getFormattedString("thresholdWarning", 
		[ cache_cert.duration, required_duration]);
    setStatus(STATE_NSEC, cache_cert.tooltip);
    if(ti.broken && ti.firstLook){
      notifyFailed(browser);
    }
  }
  else { //Its secure
    ti.notary_valid = true; 
    cache_cert.tooltip = strbundle.getFormattedString("verifiedMessage", 
		[ cache_cert.duration, required_duration]);
    setStatus(STATE_SEC, cache_cert.tooltip);
    if (ti.broken){
      ti.broken = false;
      ti.exceptions_enabled = root_prefs.getBoolPref(
				"perspectives.exceptions.enabled")
      if(ti.exceptions_enabled) { 
  	ti.isTemp = !root_prefs.getBoolPref("perspectives.exceptions.permanent");
	do_override(browser, ti.cert, ti.isTemp);
      	cache_cert.identityText = strbundle.getString("exceptionAdded");  
      	// don't give drop-down if user gave explicit
      	// permission to query notaries
      	if(ti.firstLook && !has_user_permission){
        	notifyOverride(browser);
      	}
      }
    }
  }

  if(cache_cert.identityText){
    setFaviconText(cache_cert.identityText);
  }

  ti.broken = false;
 
  } catch (err) {
    alert("done_querying_notaries error: " + err);
  }
}



//note can use request to suspend the loading
var notaryListener = { 

  /* Note can use state is broken to listen if we need to do special stuff for
   * redirecting */
  onLocationChange: function(aWebProgress, aRequest, aURI) {
      try{ 
      	d_print("main", "Location change " + aURI.spec + "\n");
      	updateStatus(gBrowser,false);
      } catch(err){
        d_print("error", "Perspectives had an internal exception: " + err);
	setStatus(STATE_ERROR, "Perspectives: an internal error occurred: " + err); 
      } 
  },

   onStateChange: function(aWebProgress, aRequest, aFlag, aStatus) { 
     var uri = gBrowser.currentURI;
     d_print("main", "State change " + uri.spec + "\n");
     if(aFlag & STATE_STOP){
       try { 
         updateStatus(gBrowser,false);
       } catch (err) { 
         d_print("error", "Perspectives had an internal exception: " + err);
	 setStatus(STATE_ERROR, "Perspectives: an internal error occurred: " + err); 
       } 
     }
  },

	onSecurityChange:    function() { },
	onStatusChange:      function() { },
	onProgressChange:    function() { },
	onLinkIconAvailable: function() { }
};

function init_whitelist(){
  var req = XMLHttpRequest();

  function parse(){ 
    if (req.readyState != 4){ 
      return;
    }
    whitelist = req.responseText.split("\n");
    for(var i = 0; i < whitelist.length; i++){
      d_print("main", "(" + whitelist[i] + ")" + "\n");
    }
  } 

  //Do it this way so we don't lag while our whitelist page loads
  try{
    req.open('GET', 'chrome://perspectives_main/content/whitelist.txt', true);
    req.onreadystatechange = parse; 
    req.send(null);
  }
  catch(e){
    d_print("error", e + "\n");
    return;
  }
}

function init_notarylist(){
   var em = Components.classes["@mozilla.org/extensions/manager;1"].
         getService(Components.interfaces.nsIExtensionManager);
   var file = em.getInstallLocation(MY_ID).getItemFile(MY_ID, "http_notary_list.txt");
   var istream = Components.classes["@mozilla.org/network/file-input-stream;1"].
                        createInstance(Components.interfaces.nsIFileInputStream);
   istream.init(file, 0x01, 0444, 0);
   istream.QueryInterface(Components.interfaces.nsILineInputStream);

   // read lines into array
   var line = {}, lines = [], hasmore;
   do {
      hasmore = istream.readLine(line)
      if (line.value.length > 0 && line.value[0] != "#") 
      	lines.push(line.value); 
   } while(hasmore);

   istream.close();
   
   var i = 0; 
   while(i < lines.length) {  
      var notary_server = { "host" : lines[i++] }; 
      if(i >= lines.length || lines[i++].indexOf("BEGIN PUBLIC KEY") == -1) { 
	alert("Perspectives: invalid notary_list.txt file: " + lines[i - 1]); 
	return; 
      }
      var key = ""; 
      while(i < lines.length && lines[i].indexOf("END PUBLIC KEY") == -1) { 
    	key += lines[i++]; 
      }
      i++; // consume the 'END PUBLIC KEY' line
      notary_server["public_key"] = key; 
      notaries.push(notary_server);  
   } 
}

function requeryAllTabs(b){
  var num = b.browsers.length;
  for (var i = 0; i < num; i++) {
    var browser = b.getBrowserAtIndex(i);
    updateStatus(browser, false);
  }
}
 
// Use Ajax to update the notary_list.txt file stored in the extension directory
// this is called on start-up  
  //NOTE: disabling auto-update of the notary list
  // b/c it could allow an attacker with a bogus root 
  // cert to compromise the system.  We should have this
  // update include a signature. 
function update_notarylist() { 
  try {
      var request = new XMLHttpRequest();
      request.open("GET","https://www.networknotary.org/notary_list.txt",true);
      request.onload = {
        handleEvent : 
		function(evt) {
    			var psv_id = "perspectives@cmu.edu"; 
    			var em = Components.classes["@mozilla.org/extensions/manager;1"].
         getService(Components.interfaces.nsIExtensionManager);
			var file = em.getInstallLocation(psv_id).getItemFile(psv_id, "notary_list.txt");
			// file is nsIFile, data is a string
			var t = request.responseText;
			d_print("main", "updating notary list to:"); 
			d_print("main", t);  
			var foStream = Components.classes["@mozilla.org/network/file-output-stream;1"].createInstance(Components.interfaces.nsIFileOutputStream);

			// use 0x02 | 0x10 to open file for appending.
			foStream.init(file, 0x02 | 0x08 | 0x20, 0666, 0); 
			foStream.write(t, t.length);
			foStream.close();
                }
        };
      request.onerror = {
        handleEvent : function(evt) {
                  d_print("error", "failed to update notary_list.txt");
            }
        };

  request.send("");

  } catch (e) {
        d_print("error", "error updating notary_list.txt: " + e);
  }
} 

function initNotaries(){
  d_print("main", "\nPerspectives Initialization\n");
  setStatus(STATE_NEUT, "");
  init_notarylist(); 
  init_whitelist();
  getBrowser().addProgressListener(notaryListener, 
      Components.interfaces.nsIWebProgress.NOTIFY_STATE_DOCUMENT);
  setTimeout(function (){ requeryAllTabs(gBrowser); }, 4000);
  d_print("main", "Perspectives Finished Initialization\n\n");

}

