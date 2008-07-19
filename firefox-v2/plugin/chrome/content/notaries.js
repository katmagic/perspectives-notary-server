/*Handles querying the notaries and updating the browser */

/* Data*/
var ssl_cache = new Object();

function clear_cache(){
  ssl_cache = new Object();
}

//certificate used in caching
function SslCert(host, port, md5, summary, duration, secure){
  this.host     = host;
  this.port     = port;
  this.md5      = md5;
  this.secure   = secure;
  this.duration = duration;
  this.summary  = summary;
}

function get_invalid_cert_SSLStatus(){
  try {
    var recentCertsSvc = 
      Components.classes["@mozilla.org/security/recentbadcerts;1"]
      .getService(Components.interfaces.nsIRecentBadCertsService);
    if (!recentCertsSvc)
      return null;

    var uri = gBrowser.currentURI;
    var port = uri.port; 
    if(port == -1) 
      port = 443; 

    var hostWithPort = uri.host + ":" + port;
    var gSSLStatus = recentCertsSvc.getRecentBadCert(hostWithPort);
    if (!gSSLStatus)
      return null;
    return gSSLStatus;
  }
  catch (e) {
    alert("exception: " + e); 
    return null;
  }
}

function cert_from_SSLStatus(gSSLStatus){
  return gSSLStatus.QueryInterface(Components.interfaces.nsISSLStatus)
    .serverCert;
}

// gets current certificat, if it FAILED the security check 
function psv_get_invalid_cert() { 
  var gSSLStatus = get_invalid_cert_SSLStatus();
  if(!gSSLStatus){
    return null;
  }
  return cert_from_SSLStatus(gSSLStatus);
} 

// gets current certificate, if it PASSED the browser check 
function psv_get_valid_cert() { 
  try { 
    var ui = gBrowser.securityUI; 
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

function getCertificate(){
 var cert = psv_get_valid_cert();
 if(!cert){
   cert = psv_get_invalid_cert();  
 }

 if(!cert) {
   return null;
 }
 return cert;
}

/* Takes an SslCert Returns a Notary Response*/
function queryNotaries(){

  var cert = psv_get_valid_cert();
  if(!cert)
    cert = psv_get_invalid_cert();  
  if(!cert) { 
    alert("No certificate found for: " + gBrowser.currentURI.host); 
    return; 
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
      alert("Perspectives component (" + cid + ") not installed correctly"); 
      return; 
    } 	
    obj = class_obj.createInstance();
    comp = obj.QueryInterface(Components.interfaces.IPerspectives);
    res = comp.do_notary_check(service_id,cert.md5Fingerprint,dir.path); 
    if(res != "") { 
      alert("Notary Error: " + res);
      return;  
    } 

    var root_prefs = Components.classes["@mozilla.org/preferences-service;1"]
      .getService(Components.interfaces.nsIPrefBranchInternal);
    var info = root_prefs.getCharPref("perspectives.info");
    var is_consistent = root_prefs.getBoolPref("perspectives.is_consistent");
    var quorum_duration = 
      root_prefs.getCharPref("perspectives.quorum_duration");
    var str = "Notary Lookup for:\n" + service_id + 
      "\nwith key = " + cert.md5Fingerprint + "\n"; 
    str += "Results:\n"; 
    str += "Quorum duration = " + quorum_duration + " days\n"; 
    str += "is_consistent = " + is_consistent + "\n"; 
    str += "Notary Observations: \n" + info; 
  } 
  catch (err) {
    alert(err);
    return;
  }

  function NotaryResponse(summary, duration, consistent){
    this.duration   = duration;
    this.consistent = consistent;
    this.summary    = summary;
  }

  return new NotaryResponse(str, quorum_duration, is_consistent);
} 

  
/* There is a bug here.  Sometimes it gets into a browser reload 
 * loop.  Come back to this later */

function do_override(location) { 
  dump("Do Override\n");
  var gSSLStatus = get_invalid_cert_SSLStatus();
  if(!gSSLStatus){ //this paged loaded properly so don't do anythign
    dump("No invalid cert \n");
    return false;
  }
  var cert = cert_from_SSLStatus(gSSLStatus);
  if(!cert){
    dump("Error getting certificate from ssl\n");
    return;
  }

	var uri = gBrowser.currentURI;  
	var overrideService = 
    Components.classes["@mozilla.org/security/certoverride;1"]
		.getService(Components.interfaces.nsICertOverrideService);
    

  var flags = 0;
  if(gSSLStatus.isUntrusted)
    flags |= overrideService.ERROR_UNTRUSTED;
  if(gSSLStatus.isDomainMismatch)
    flags |= overrideService.ERROR_MISMATCH;
  if(gSSLStatus.isNotValidAtThisTime)
    flags |= overrideService.ERROR_TIME;

  if(overrideService.isCertUsedForOverrides(
        cert,true,true)){
    dump("Already Override\n");
    return;
  }

	overrideService.rememberValidityOverride(
			uri.asciiHost, uri.port, cert, flags, true);
 
  //Possible browser reload loop here
  //hack
  //16 specifies that its a reload
  dump("Reload page: " + location.spec + "\n");
  setTimeout(function (){ gBrowser.loadURIWithFlags(
        location.spec, gBrowser.LOAD_FLAGS_IS_REFRESH);}, 250);
  return true;
}

function setStatusSecure(){
  dump("Secure Status\n");
  document.getElementById("perspective-status-image")
    .setAttribute("hidden", "false");
  document.getElementById("perspective-status-image")
    .setAttribute("src", "chrome://perspectives/content/good.png");
  return true;
}

function setStatusUnsecure(){
  dump("Unsecure Status\n");
  document.getElementById("perspective-status-image")
    .setAttribute("hidden", "false");
  document.getElementById("perspective-status-image")
    .setAttribute("src", "chrome://perspectives/content/bad.png");
  return true;
}

function setStatusNeutral(){
  dump("Neutral Status\n");
  document.getElementById("perspective-status-image")
    .setAttribute("hidden", "true");
  return true;
}

/* Updates the status of the current page */
//Make this a bit more efficient when I get a chance
function updateStatus(location){

  if(!location || location.scheme != "https"){
    setStatusNeutral();
    return;
  }
  dump("Update Status: ");
  dump(location.spec);
  dump("\n");

  var cert = getCertificate();
  if(!cert){
    dump("Couldn't find md5 the page hasn't finished loading\n");
    return;
  }
  var md5 = cert.md5Fingerprint;

  if(!ssl_cache[location.host] || ssl_cache[location.host].md5 != md5){
    var resp = queryNotaries();
    ssl_cache[location.host] = new SslCert(location.host, 
          location.port, md5, resp.summary, 
          resp.duration, resp.consistent);
  }
  cache_cert = ssl_cache[location.host];

  var root_prefs = Components.classes["@mozilla.org/preferences-service;1"]
    .getService(Components.interfaces.nsIPrefBranchInternal);
  var required_duration = 
    root_prefs.getIntPref("perspectives.required_duration") / 100.0;
  if(cache_cert.secure && cache_cert.duration >= required_duration){
    setStatusSecure();
    do_override(location);
  }
  else{
    setStatusUnsecure();
  }
}

//note can use request to suspend the loading
var notaryListener = { 
	/* If something changes in the locationation bar */
onLocationChange: function(webProgress, request, location) {
    dump("\nLocation changed \n");
    updateStatus(location);
	},

	onStateChange: function(webProgress, request, stateFlags, status) {
	},

	onProgressChange: function(webProgress, request, curSelfProgress, 
    maxSelfProgress, curTotalProgress, maxTotalProgress) {
	},

	onSecurityChange: function(webProgress, request, state) {
	},

	onStatusChange: function(webProgress, request, status, message) {
    //This is just a hack for now I really need to figure out
    //race condition stuff
    updateStatus(gBrowser.currentURI);
	},

	onLinkIconAvailable: function() {
	}
};

var pageLoadEvent = {
  init: function(){
    dump("init init");
    var appcontent = document.getElementByID("appcontent");
    if(appcontent){
      appcontent.addEventListener("DOMContentLoaded", this.onPageLoad, true);
    }
  },

  onPageLoad: function(aEvent) {
    var doc = aEvent.originalTarget;
    dump("\nOnPageLoad " + doc.location.host + "\n");
    updateStatus(doc.location);
  }
}

function initNotaries(){
  document.getElementById("perspective-statusbar-label")
    .setAttribute("hidden", "false");
  document.getElementById("perspective-status-image")
    .setAttribute("hidden", "true");
  getBrowser().addProgressListener(notaryListener, 
      Components.interfaces.nsIWebProgress.NOTIFY_STATE_DOCUMENT);
}
