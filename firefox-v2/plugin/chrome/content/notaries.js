/* Data */
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

function do_override(uri, cert) { 
  dump("Do Override\n");

  gSSLStatus = get_invalid_cert_SSLStatus();
  var flags = 0;
  if(gSSLStatus.isUntrusted)
    flags |= overrideService.ERROR_UNTRUSTED;
  if(gSSLStatus.isDomainMismatch)
    flags |= overrideService.ERROR_MISMATCH;
  if(gSSLStatus.isNotValidAtThisTime)
    flags |= overrideService.ERROR_TIME;

	overrideService.rememberValidityOverride(
			uri.asciiHost, uri.port, cert, flags, true);

  return true;
}

function setStatus(state){
  var i = document.getElementById("perspective-status-image");
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

  dump("Update Status: " + uri.spec + "\n");
  broken         = false;
  var cert       = getCertificate();
  var md5        = cert.md5Fingerprint;
  var state      = gBrowser.securityUI.state;
  var gSSLStatus = null;
  var duration   = 
    root_prefs.getIntPref("perspectives.required_duration") / 100.0;

  if ((state & STATE_IS_BROKEN || state & STATE_IS_INSECURE) &&
      !overrideService.isCertUsedForOverrides(cert,true,true)){
    broken = true; 
    /*
    gBrowser.stop();
    var flags = gBrowser.LOAD_FLAGS_BYPASS_HISTORY;
    gBrowser.loadURIWithFlags(
      "chrome://perspectives_main/content/help.html", flags);
     this doesn't work */
  }

  //Update ssl cache cert
  if(!ssl_cache[uri.host] || ssl_cache[uri.host].md5 != md5){
    var resp = queryNotaries();
    ssl_cache[uri.host] = new SslCert(uri.host, 
      uri.port, md5, resp.summary, resp.duration, resp.consistent);
  }
  cache_cert = ssl_cache[uri.host];

  var secure = cache_cert.secure && cache_cert.duration >= duration;

  if(secure){
    setStatus(STATE_SEC);
    if (broken){
      var flags = gBrowser.LOAD_FLAGS_IS_REFRESH;
      broken = false;
      do_override(uri, cert);
      /*setTimeout(function (){ 
        gBrowser.loadURIWithFlags(uri.spec, flags);}, 5);*/
      setTimeout(function (){ gBrowser.reload();}, 25);
    }
  }
  else{
    setStatus(STATE_NSEC);
  }

  broken = false;
}

//note can use request to suspend the loading
var notaryListener = { 

  /* Note can use state is broken to listen if we need to do special stuff for
   * redirecting */
  onLocationChange: function(aWebProgress, aRequest, aURI) {
      dump("\nLocation changed \n");
      if(!aURI || aURI.scheme != "https"){
        setStatus(STATE_NEUT);
        return;
      }
      updateStatus(aURI);
  },

	onStateChange: function(aWebProgress, aRequest, aFlag, aStatus) { 
    var uri = gBrowser.currentURI;
    if(!uri || uri.scheme != "https"){
      setStatus(STATE_NEUT);
      return;
    }
    else if(aFlag & STATE_STOP){
      dump("\nPage Finished Loading\n");
      updateStatus(gBrowser.currentURI);
    }
  },

	onSecurityChange:    function(aWebProgress, aRequest, aState){ },
	onStatusChange:      function() { },
	onProgressChange:    function() { },
	onLinkIconAvailable: function() { }
};

function initNotaries(){
  document.getElementById("perspective-status-image")
    .setAttribute("hidden", "true");
  getBrowser().addProgressListener(notaryListener, 
      Components.interfaces.nsIWebProgress.NOTIFY_STATE_DOCUMENT);
}
