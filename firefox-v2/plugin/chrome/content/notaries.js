var STATE_IS_BROKEN   = 
  Components.interfaces.nsIWebProgressListener.STATE_IS_BROKEN;
var STATE_IS_INSECURE = 
  Components.interfaces.nsIWebProgressListener.STATE_IS_INSECURE;
var STATE_IS_SECURE = 
  Components.interfaces.nsIWebProgressListener.STATE_IS_SECURE;

var nonrouted_ips = [ "^192\.168\.", "^10.", "^172\.1[6-9]\.", 
			"^172\.2[0-9]\.", "172\.3[0-1]\.", "^169\.254\.", 
			"^127\.0\.0\.1$"]; // could add many more


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
	d_print("unreachable ip = " + ip_str + "\n");  
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

// if the tab changes to a webpage that has no notary
// results, set the 'reason' property of this object to explain why.  
// I use this hack b/c ssl_cache only caches info for sites we have
// probed, wherease we want to communicate info to the status pop-up
// about sites we haven't probed. 
var other_cache = {}; 
other_cache["debug"] = ""; 

function clear_cache(){
  ssl_cache = new Object();
}

function d_print(line) { 
	dump(line); 
	other_cache["debug"] += line; 
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
		d_print("clear_existing_banner error: " + err); 	
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
  var message = 
    "Perspectives has verified the security of your "
    + "connection to this website and has bypassed Firefox's "
    + "security error page";
  var buttons = [{
    accessKey : "", 
    label: "Learn More", 
    accessKey : "", 
    callback: function() {
      b.loadOneTab(
      "chrome://perspectives_main/content/help.html", null, null,
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
  var message = 
    "Suspected attack: Perspectives was unable to verify the "
    + "security of your connection to this website";
  var buttons = null;
  /* Uncomment when we have some sort of system
  var buttons = [{
    label: "Report This", 
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
  var message = 
    "Perspectives may be able to override this security error " +
    " by contacting Network Notary servers, but needs your permission.";
  var buttons = null;
  var buttons = [
    {
    label: "Yes, contact Notaries", 
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
          d_print("successfully removed all notifications\n");  
        } 
        catch (err2) { 
          d_print("probe_permission error2:" + err2 + "\n"); 
        } 
        d_print("probe_permission error1: " + err + "\n"); 
      } 
      // run probe
      d_print("User gives probe permission\n"); 
      var uri = b.currentURI;
      updateStatus(b,true); 
    }},
    { 
    label: "Learn More",
    accessKey : "", 
    callback: function() {
      b.loadOneTab(
      "chrome://perspectives_main/content/help.html", null, null,
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
  var message = 
    "Warning: Perspectives received no notary replies. " +
    "This may be an attack or you may be behind a firewall/proxy that blocks notary requests.";
  var buttons = null;
  var buttons = [
    { 
    label: "Firewall/Proxy Help",
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
      d_print("Whitelisted: " + whitelist[i] + "\n");
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
    d_print("Perspectives Error: " + e); 
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

/* Takes an SslCert Returns a Notary Response*/
function queryNotaries(cert, uri){

  root_prefs.setCharPref("perspectives.info", "");
  root_prefs.setBoolPref("perspectives.is_consistent", true);
  root_prefs.setCharPref("perspectives.quorum_duration", "");
  root_prefs.setCharPref("perspectives.svg", "");

  if(!cert) { 
    d_print("No certificate found for: " + uri.host); 
    return null; 
  } 

  var port = uri.port; 
  if(port == -1) 
    port = 443; 
  service_id = uri.host + ":" + port + ",2"; 

  try { 
    var man = Components.classes["@mozilla.org/extensions/manager;1"]
      .getService(Components.interfaces.nsIExtensionManager);

    var il = man.getInstallLocation("perspectives@cmu.edu");
    var dir = il.location; 
    dir.append("perspectives@cmu.edu"); 

    const cid = "@cs.cmu.edu/Perspectives;1";
    //obj = Components.classes[cid].createInstance();
    class_obj = Components.classes[cid]; 
    if(!class_obj) { 
      alert("Perspectives component (" + cid + ") not installed correctly."
        + " Please report information about your platform to developers"); 
      return null; 
    } 	
    
    obj = class_obj.createInstance();
    comp = obj.QueryInterface(Components.interfaces.IPerspectives);
    res = comp.do_notary_check(service_id,cert.md5Fingerprint,dir.path); 
    if(res != "") { 
      d_print("Notary XPCOM Error: " + res);
      return null;  
    } 

    var quorum_duration = 
      root_prefs.getCharPref("perspectives.quorum_duration");
    if(quorum_duration == ""){ //Make sure everything completed properyl
      return null;
    }
    var info = root_prefs.getCharPref("perspectives.info");
    var is_consistent = root_prefs.getBoolPref("perspectives.is_consistent");
    var str = "Notary Lookup for: " + service_id + "\n";
    str += "Key = " + cert.md5Fingerprint + "\n"; 
    str += "Results:\n\n"; 
    str += "Quorum duration: " + quorum_duration + " days\n"; 
    str += "Notary Observations: \n" + info; 
    d_print("\n\n" + str + "\n\n");

    var svg = root_prefs.getCharPref("perspectives.svg");
  } 
  catch (err) {
    d_print("queryNotaries error: " + err);
    return null;
  }

  function NotaryResponse(summary, svg, duration, consistent){
    this.duration   = duration;
    this.consistent = consistent;
    this.summary    = summary;
    this.svg        = svg;
  }

  return new NotaryResponse(str, svg, quorum_duration, is_consistent);
} 

  
/* There is a bug here.  Sometimes it gets into a browser reload 
 * loop.  Come back to this later */

function do_override(browser, cert) { 
  var uri = browser.currentURI;
  d_print("Do Override\n");
  if(!root_prefs.getBoolPref("perspectives.exceptions.enabled")){
    return;
  }

  gSSLStatus = get_invalid_cert_SSLStatus(uri);
  var flags = 0;
  if(gSSLStatus.isUntrusted)
    flags |= overrideService.ERROR_UNTRUSTED;
  if(gSSLStatus.isDomainMismatch)
    flags |= overrideService.ERROR_MISMATCH;
  if(gSSLStatus.isNotValidAtThisTime)
    flags |= overrideService.ERROR_TIME;

  var isTemp = ! root_prefs.getBoolPref("perspectives.exceptions.permanent");
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
  d_print("Update Status\n");
  if(!browser){
    d_print("No Browser!!\n");
    return;
  }
  var uri = browser.currentURI;
  if(!uri) { 
    var text = "Perspectives: No Data. Browser provided an empty URI for " + 
      "this connection. Try hitting refresh.";
    setStatus(STATE_NEUT,text); 
    other_cache["reason"] = text;
    return;
  } 
  if(!uri.host){
    return;
  }
  d_print("Update Status: " + uri.spec + "\n");

  if(uri.scheme != "https"){
    var text = "Perspectives:  Notaries are only contacted for HTTPS " +
      "enabled websites.  Your connection to " + uri.host + " uses '" + uri.scheme + "'.";
    setStatus(STATE_NEUT,text); 
    other_cache["reason"] = text;
    return;
  } 
  if(onWhitelist(uri.host)){
    var text = "Perspectives: " + uri.host + " is known to use " + 
      "inconsistent keys in normal operation, so Perspectives is configured ignore it.";
    setStatus(STATE_NEUT,text); 
    other_cache["reason"] = text; 
    return;
  }
  var unreachable = host_is_unreachable(uri.host); 
  if(unreachable) { 
    var text = "Perspectives: No Information. " 
      + "All IPs (" + unreachable + ") associated with " + uri.host + 
	" are in a private local network.";
    setStatus(STATE_NEUT,text); 
    other_cache["reason"] = text; 
    return;
  } 

  broken         = false;
  var cert       = getCertificate(browser);
  if(!cert){
    var text = "Perspectives: No information.  The browser was unable to " 
      + "retrieve a certificate for " + uri.host;  
    setStatus(STATE_NEUT,text); 
    other_cache["reason"] = text; 
    return;
  }
  var md5        = cert.md5Fingerprint;
  var state      = browser.securityUI.state;
  var gSSLStatus = null;
  var duration   = 
    root_prefs.getIntPref("perspectives.required_duration") / 100.0;

  var is_override_cert = overrideService.isCertUsedForOverrides(cert, true, true);
  d_print("is_override_cert = " + is_override_cert + "\n"); 
  var check_good = root_prefs.getBoolPref("perspectives.check_good_certificates"); 

  if(state & STATE_IS_SECURE) { 
    d_print("clearing any existing permission banners\n"); 
    clear_existing_banner(browser, "Perspecives-Permission"); 
  }

  // see if the browser has this cert installed prior to this browser session
  var already_trusted = (state & STATE_IS_SECURE) && 
    !(is_override_cert && ssl_cache[uri.host]); 
  if(!check_good && already_trusted) {
    var text =  "Perspectives: No Information. Your preferences are set to query notaries "
	+ "only for HTTPS certificates that fail browser security checks.";
    setStatus(STATE_NEUT,text); 
    other_cache["reason"] = text; 
    return;
  } 

  if(!is_override_cert && state & STATE_IS_INSECURE){
    d_print("state is STATE_IS_INSECURE, we need an override\n");
    broken = true; 
  }

  //Update ssl cache cert
  var firstLook = false;
  if(!ssl_cache[uri.host] || ssl_cache[uri.host].md5 != md5){
    firstLook = true;
    d_print(uri.host + " needs a request\n"); 
    var needs_perm = root_prefs.getBoolPref("perspectives.require_user_permission"); 
    if(needs_perm && !has_user_permission) {
      d_print("needs user permission\n");  
      notifyNeedsPermission(browser);
      var text = "Perspectives: No Information. Your preferences indicate that Perspectives "
        + "should not contact Notaries without your permission.";
      setStatus(STATE_NEUT,text); 
      other_cache["reason"] = text;  
      return; 
    } 
    d_print("Contacting notary\n"); 
    var resp = queryNotaries(cert, uri);
    if(!resp){
      var text = "Perspectives: An internal error occurred: " + resp; 
      setStatus(STATE_ERROR, text);
      return;
    }
    var temp = new SslCert(uri.host, 
        uri.port, md5, resp.summary, null, resp.svg, resp.duration, resp.consistent);
    ssl_cache[uri.host] = temp;
  }

  cache_cert = ssl_cache[uri.host];
  if( !broken && 
      !cache_cert.identityText &&
      getFaviconText().indexOf("Perspectives") < 0){
    cache_cert.identityText = 
    setFaviconText(getFaviconText() + "\n\n" + 
    "Perspectives has validated this site");
  }

  if (cache_cert.summary.indexOf("ssl key") == -1) { 
    	cache_cert.tooltip = "Warning: Perspectives received no Notary replies.";
    	setStatus(STATE_NSEC, cache_cert.tooltip);
	if(broken) { 
	  notifyNoReplies(browser); 
	} 
  } else if(!cache_cert.secure){
    cache_cert.tooltip = "Warning: Perspectives has NOT seen this certificate consistently";
    setStatus(STATE_NSEC, cache_cert.tooltip);
    if(broken && firstLook){
      notifyFailed(browser);
    }
  }
  else if(cache_cert.duration < duration){
    cache_cert.tooltip = 
      "Warning: Perspectives has seen this certificate consistently for only " 
	+ cache_cert.duration + " days, threshold is " + duration + " days";
    setStatus(STATE_NSEC, cache_cert.tooltip);
    if(broken && firstLook){
      notifyFailed(browser);
    }
  }
  else { //Its secure
    cache_cert.tooltip = 
      "Verified: Perpsectives has seen this certificate consistently for " + cache_cert.duration +
      " days, threshold is " + duration + " days";
    setStatus(STATE_SEC, cache_cert.tooltip);
    if (broken){
      broken = false;
      do_override(browser, cert);
      cache_cert.identityText = 
        "Perspectives has added a security exception for this site";
      // don't give drop-down if user gave explicit
      // permission to query notaries
      if(firstLook && !has_user_permission){
        notifyOverride(browser);
      }
    }
  }

  if(cache_cert.identityText){
    setFaviconText(cache_cert.identityText);
  }

  broken = false;
}

//note can use request to suspend the loading
var notaryListener = { 

  /* Note can use state is broken to listen if we need to do special stuff for
   * redirecting */
  onLocationChange: function(aWebProgress, aRequest, aURI) {
      try{ 
      	d_print("Location change " + aURI.spec + "\n");
      	updateStatus(gBrowser,false);
      } catch(err){
        d_print("Perspectives had an internal exception: " + err);
	setStatus(STATE_ERROR, "Perspectives: an internal error occurred: " + err); 
      } 
  },

   onStateChange: function(aWebProgress, aRequest, aFlag, aStatus) { 
     var uri = gBrowser.currentURI;
     d_print("State change " + uri.spec + "\n");
     if(aFlag & STATE_STOP){
       try { 
         updateStatus(gBrowser,false);
       } catch (err) { 
         d_print("Perspectives had an internal exception: " + err);
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
    dump("Whitelist length " + whitelist.length + "\n");
    for(var i = 0; i < whitelist.length; i++){
      dump("(" + whitelist[i] + ")" + "\n");
    }
  } 

  //Do it this way so we don't lag while our whitelist page loads
  try{
    req.open('GET', 'chrome://perspectives_main/content/whitelist.txt', true);
    req.onreadystatechange = parse; 
    req.send(null);
  }
  catch(e){
    d_print(e + "\n");
    return;
  }
}

function requeryAllTabs(b){
  var num = b.browsers.length;
  for (var i = 0; i < num; i++) {
    var browser = b.getBrowserAtIndex(i);
    updateStatus(browser, false);
  }
}

function initNotaries(){
  dump("\nPerspectives Initialization\n");
  setStatus(STATE_NEUT, "");
  init_whitelist();
  getBrowser().addProgressListener(notaryListener, 
      Components.interfaces.nsIWebProgress.NOTIFY_STATE_DOCUMENT);
  setTimeout(function (){ requeryAllTabs(gBrowser); }, 4000);
  dump("Perspectives Finished Initialization\n\n");
}
