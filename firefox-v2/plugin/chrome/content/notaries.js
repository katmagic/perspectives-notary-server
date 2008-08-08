/* Data */
var whitelist     = new Array();
var ssl_cache     = new Object();
var root_prefs    = Components.classes["@mozilla.org/preferences-service;1"]
  .getService(Components.interfaces.nsIPrefBranchInternal);
var overrideService = 
  Components.classes["@mozilla.org/security/certoverride;1"]
  .getService(Components.interfaces.nsICertOverrideService);
var broken = false;

const STATE_SEC   = 0;
const STATE_NSEC  = 1;
const STATE_NEUT  = 2;
const STATE_START = Components.interfaces.nsIWebProgressListener.STATE_START;
const STATE_STOP  = Components.interfaces.nsIWebProgressListener.STATE_STOP;
const STATE_IS_BROKEN   = 
  Components.interfaces.nsIWebProgressListener.STATE_IS_BROKEN;
const STATE_IS_INSECURE = 
  Components.interfaces.nsIWebProgressListener.STATE_IS_INSECURE;


function clear_cache(){
  ssl_cache = new Object();
}


function notifyOverride(){
  var notificationBox = gBrowser.getNotificationBox(browser);

  var oldNotification = 
    notificationBox.getNotificationWithValue("Perspectives");
  if(oldNotification != null){
    notificationBox.removeNotification(oldNotification);
  }

  var priority = notificationBox.PRIORITY_INFO_LOW;
  var message = 
    "Perspectives has verified the security of your "
    + "connection to this website and has bypassed Firefox's "
    + "security error page";
  var buttons = [{
    label: "Learn More", 
    callback: function() {
      gBrowser.loadOneTab(
      "chrome://perspectives_main/content/help.html", null, null,
      null, false);
    }
  }];
    
  notificationBox.appendNotification(message, "Perspectives", null,
    priority, buttons);
}

function notifyFailed(){
  var notificationBox = gBrowser.getNotificationBox(browser);

  var oldNotification = 
    notificationBox.getNotificationWithValue("Perspectives");
  if(oldNotification != null){
    notificationBox.removeNotification(oldNotification);
  }

  var priority = notificationBox.PRIORITY_CRITICAL_LOW;
  var message = 
    "Suspected attack: Perspectives was unable to verify the "
    + "security of your connection to this website";
  var buttons = null;
  /* Uncomment when we have some sort of system
  var buttons = [{
    label: "Report This", 
    callback: function() {
      alert("Do Stuff");
    }
  }];
  */
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
  dump(length + "\n");
  for(var i = 0; i < length; i++){
    if(whitelist[i] == ""){//don't know why i need this
      continue;
    }
    if(host.indexOf(whitelist[i]) >= 0){
      dump("Whitelisted: " + whitelist[i] + "\n");
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
function psv_get_valid_cert() { 
  try { 
    var ui = gBrowser.securityUI; 
    dump(ui.state +
    "-----------------------------------------------------------------------\n");
    ui.QueryInterface(Components.interfaces.nsISSLStatusProvider); 
    if(!ui.SSLStatus) 
      return null; 
    return ui.SSLStatus.serverCert; 
  }
  catch (e) {
    alert("Perspectives Error: " + e); 
    return null;
  }
} 

function getCertificate(uri){
  var cert = psv_get_valid_cert();
  if(!cert){
    cert = psv_get_invalid_cert(uri);  
  }

  if(!cert) {
    return null;
  }
  return cert;
}

/* Takes an SslCert Returns a Notary Response*/
function queryNotaries(cert){

  root_prefs.setCharPref("perspectives.info", "");
  root_prefs.setBoolPref("perspectives.is_consistent", true);
  root_prefs.setCharPref("perspectives.quorum_duration", "");
  root_prefs.setCharPref("perspectives.svg", "");

  if(!cert) { 
    alert("No certificate found for: " + gBrowser.currentURI.host); 
    return null; 
  } 

  uri = gBrowser.currentURI;  
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
        + " Please report this bug to the developers"); 
      return null; 
    } 	
    obj = class_obj.createInstance();
    comp = obj.QueryInterface(Components.interfaces.IPerspectives);
    res = comp.do_notary_check(service_id,cert.md5Fingerprint,dir.path); 
    if(res != "") { 
      alert("Notary Error: " + res);
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
    dump("\n\n" + str + "\n\n");

    var svg = root_prefs.getCharPref("perspectives.svg");
  } 
  catch (err) {
    alert(err);
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

function do_override(uri, cert) { 
  dump("Do Override\n");
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
    gBrowser.loadURIWithFlags(uri.spec, flags);}, 25);
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
      dump("Secure Status\n");
      i.setAttribute("hidden", "false");
      i.setAttribute("src", "chrome://perspectives/content/good.png");
      break;
    case STATE_NSEC:
      dump("Unsecure Status\n");
      i.setAttribute("hidden", "false");
      i.setAttribute("src", "chrome://perspectives/content/bad.png");
      break;
    case STATE_NEUT:
      dump("Neutral Status\n");
      i.setAttribute("hidden", "true");
      break;
  }
  return true;
}

/* Updates the status of the current page */
//Make this a bit more efficient when I get a chance
function updateStatus(uri){

  if(!uri || uri.scheme != "https"){
    setStatus(STATE_NEUT,
     "No Information:  Perspectives only provides information about" +
     " HTTPS enabled websites");
    return;
  } 
  if(onWhitelist(uri.host)){
    setStatus(STATE_NEUT, "No Information: Perspectives intentionally " 
      + "does not probe " + uri.host + " because this website uses " + 
      "inconsistent keys in normal operation.");
    return;
  }

  if(uri.host != gBrowser.currentURI.host){
    dump("\n---------------THE WORLD HAS ENDED------------\n");
  }

  dump("Update Status: " + uri.spec + "\n");
  broken         = false;
  var cert       = getCertificate(uri);
  if(!cert){
    return;
  }
  var md5        = cert.md5Fingerprint;
  var state      = gBrowser.securityUI.state;
  var gSSLStatus = null;
  var duration   = 
    root_prefs.getIntPref("perspectives.required_duration") / 100.0;

  if((state & STATE_IS_BROKEN)){ //This means that the cert hasn't downloaded
    dump("State is broken\n");
    return;
  }

  if(!overrideService.isCertUsedForOverrides(cert, true, true)){
    if (state & STATE_IS_INSECURE){
      broken = true; 
    }
    else if(!root_prefs.getBoolPref("perspectives.check_good_certificates")){
      setStatus(STATE_NEUT, 
        "No Information: Your preferences indicate that Perspectives should" 
         + " not probe websites with HTTPS certificates already trusted by "
         + "your browser.");
      return;
    }
  }

  //Update ssl cache cert
  var firstLook = false;
  if(!ssl_cache[uri.host] || ssl_cache[uri.host].md5 != md5){
    firstLook = true;
    var resp = queryNotaries(cert);
    if(!resp){
      dump("\nNotary Query Failed\n");
      return;
    }
    var temp = new SslCert(uri.host, 
      uri.port, md5, resp.summary, null, resp.svg, resp.duration, resp.consistent);
    ssl_cache[uri.host] = temp;
  }

  if(!ssl_cache[uri.host]){
    dump("\nSHOULDNT HAPPEN NO CACHE ENTRY\n");
    return;
  }
  cache_cert = ssl_cache[uri.host];

  if(!cache_cert.secure){
    cache_cert.tooltip = "Warning: Key has NOT been seen consistently";
    setStatus(STATE_NSEC, cache_cert.tooltip);
    if(broken && firstLook){
      notifyFailed();
    }
  }
  else if(cache_cert.duration < duration){
    cache_cert.tooltip = 
      "Warning: Key seen consistently for only " + cache_cert.duration + 
      " days, threshold is " + duration + " days";
    setStatus(STATE_NSEC, cache_cert.tooltip);
    if(broken && firstLook){
      notifyFailed();
    }
  }
  else { //Its secure
    cache_cert.tooltip = 
      "Key Verified: Key seen consistently for " + cache_cert.duration +
      " days, threshold is " + duration + " days";
    setStatus(STATE_SEC, cache_cert.tooltip);
    if (broken){
      broken = false;
      do_override(uri, cert);
      if(firstLook){
        notifyOverride();
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
      dump("Location change " + aURI.spec + "\n");
      updateStatus(aURI);
  },

	onStateChange: function(aWebProgress, aRequest, aFlag, aStatus) { 
    var uri = gBrowser.currentURI;
    dump("State change " + uri.spec + "\n");
    if(aFlag & STATE_STOP){
      updateStatus(uri);
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

function initNotaries(){
  dump("\nPerspectives Initialization\n");
  document.getElementById("perspective-status-image")
    .setAttribute("hidden", "true");
  init_whitelist();
  getBrowser().addProgressListener(notaryListener, 
      Components.interfaces.nsIWebProgress.NOTIFY_STATE_DOCUMENT);
  dump("Perspectives Finished Initialization\n\n");
}
