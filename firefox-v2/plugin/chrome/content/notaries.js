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

const STATE_SEC   = 0;
const STATE_NSEC  = 1;
const STATE_NEUT  = 2;
const STATE_START = Components.interfaces.nsIWebProgressListener.STATE_START;
const STATE_STOP  = Components.interfaces.nsIWebProgressListener.STATE_STOP;
const STATE_IS_BROKEN   = 
  Components.interfaces.nsIWebProgressListener.STATE_IS_BROKEN;
const STATE_IS_INSECURE = 
  Components.interfaces.nsIWebProgressListener.STATE_IS_INSECURE;
const STATE_IS_SECURE = 
  Components.interfaces.nsIWebProgressListener.STATE_IS_SECURE;



function clear_cache(){
  ssl_cache = new Object();
}

function d_print(line) { 
	dump(line); 
	other_cache["debug"] += line; 
} 

function clear_existing_banner(b, value_text) { 
  try { 
  	var notificationBox = b.getNotificationBox(browser);
  	var oldNotification = 
    	notificationBox.getNotificationWithValue(value_text);
  	if(oldNotification != null)
    		notificationBox.removeNotification(oldNotification);
 	} catch (err) { 
		d_print("clear_existing_banner error: " + err); 	
   	} 
} 

function notifyOverride(b){
  var notificationBox = b.getNotificationBox(browser);
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
  var notificationBox = b.getNotificationBox(browser);

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
  var notificationBox = b.getNotificationBox(browser);

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
            var nbox = b.getNotificationBox();
            nbox.removeCurrentNotification();
        } catch (err) {
          // sometimes, this doesn't work.  why?
          // well, we'll just have to remove them all
          try { 
            nbox.removeAllNotifications();
	    d_print("successfully removed all notifications\n");  
          } catch (err2) { 
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

function setStatus(state, tooltip){
  var i = document.getElementById("perspective-status-image");
  var t = document.getElementById("perspective-status");
  if(!tooltip){
    tooltip = "Perspectives";
  }
  t.setAttribute("tooltiptext", tooltip);
  switch(state){
    case STATE_SEC:
      d_print("Secure Status\n");
      i.setAttribute("hidden", "false");
      i.setAttribute("src", "chrome://perspectives/content/good.png");
      break;
    case STATE_NSEC:
      d_print("Unsecure Status\n");
      i.setAttribute("hidden", "false");
      i.setAttribute("src", "chrome://perspectives/content/bad.png");
      break;
    case STATE_NEUT:
      d_print("Neutral Status\n");
      i.setAttribute("hidden", "true");
      break;
  }
  d_print("changing tooltip to: " + tooltip + "\n"); 
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
    dump("No Browser!!\n");
    return;
  }
  var uri = browser.currentURI;
  if(!uri) { 
    var text = "No Information:  Perspectives received an empty URI for " + 
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
    var text = "No Information:  Perspectives only provides information about HTTPS " +
      "enabled websites.  Your connection to " + uri.host + " uses " + uri.scheme + " .";
    setStatus(STATE_NEUT,text); 
    other_cache["reason"] = text;
    return;
  } 
  if(onWhitelist(uri.host)){
    var text = "No Information: Perspectives intentionally " 
      + "does not probe " + uri.host + " because this website uses " + 
      "inconsistent keys in normal operation.";
    setStatus(STATE_NEUT,text); 
    other_cache["reason"] = text; 
    return;
  }

  broken         = false;
  var cert       = getCertificate(browser);
  if(!cert){
    var text = "No Information: Perspectives was unable to " 
      + "retrieve a certificate for: " + uri.host;  
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
    var text =  "No Information: Your preferences indicate that Perspectives should" 
      + " not probe websites with HTTPS certificates already trusted by "
      + "your browser.";
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
      var text = "No Information:  Your preferences indicate that Perspectives "
        + "should not contact Notaries without your permission.";
      setStatus(STATE_NEUT,text); 
      other_cache["reason"] = text;  
      return; 
    } 
    d_print("Contacting notary\n"); 
    var resp = queryNotaries(cert, uri);
    if(!resp){
      var text = "Perspectives experienced an internal error: " + resp; 
      setStatus(STATE_NSEC, text);
      return;
    }
    var temp = new SslCert(uri.host, 
        uri.port, md5, resp.summary, null, resp.svg, resp.duration, resp.consistent);
    ssl_cache[uri.host] = temp;
  }

  cache_cert = ssl_cache[uri.host];
  if(!cache_cert.secure){
    cache_cert.tooltip = "Warning: Key has NOT been seen consistently";
    setStatus(STATE_NSEC, cache_cert.tooltip);
    if(broken && firstLook){
      notifyFailed(browser);
    }
  }
  else if(cache_cert.duration < duration){
    cache_cert.tooltip = 
      "Warning: Key seen consistently for only " + cache_cert.duration + 
      " days, threshold is " + duration + " days";
    setStatus(STATE_NSEC, cache_cert.tooltip);
    if(broken && firstLook){
      notifyFailed(browser);
    }
  }
  else { //Its secure
    cache_cert.tooltip = 
      "Key Verified: Key seen consistently for " + cache_cert.duration +
      " days, threshold is " + duration + " days";
    setStatus(STATE_SEC, cache_cert.tooltip);
    if (broken){
      broken = false;
      do_override(browser, cert);
      // don't give drop-down if user gave explicit
      // permission to query notaries
      if(firstLook && !has_user_permission){
        notifyOverride(browser);
      }
    }
  }
  broken = false;
}

//note can use request to suspend the loading
var notaryListener = { 

  /* Note can use state is broken to listen if we need to do special stuff for
   * redirecting */
  onLocationChange: function(aWebProgress, aRequest, aURI) {
      try { 
      	d_print("Location change " + aURI.spec + "\n");
      	updateStatus(gBrowser,false);
      } catch (err) {
        d_print("Perspectives had an internal exception: " + err);
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
    dump(e + "\n");
    return;
  }
}

function requeryAllTabs(){
  dump("\nRequeryAllTabs\n");
  var num = gBrowser.browsers.length;
  for (var i = 0; i < num; i++) {
    var browser = gBrowser.getBrowserAtIndex(i);
    dump("Reload: " + browser.currentURI.spec + "\n");
    if(browser.currentURI.scheme != "https"){
      continue;
    }
    updateStatus(browser, false);
  }
  dump("\n");
}

function initNotaries(){
  dump("\nPerspectives Initialization\n");
  document.getElementById("perspective-status-image")
    .setAttribute("hidden", "true");
  init_whitelist();
  getBrowser().addProgressListener(notaryListener, 
      Components.interfaces.nsIWebProgress.NOTIFY_STATE_DOCUMENT);
  setTimeout(function (){ requeryAllTabs(); }, 1200);
  dump("Perspectives Finished Initialization\n\n");
}
