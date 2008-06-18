/*Handles querying the notaries and updating the browser */

/* Data*/
var ssl_cache = new Object();

function SslCert(host, port, md5, secure){
  this.host     = host;
  this.port     = port;
  this.md5      = md5;
  this.secure   = secure;
  this.quorum   = 0;
  this.duration = 0;
}

function NotaryResponse(quorum, duration){
  this.quorum   = quorum;
  this.duration = duration;
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

function getFingerprint() { 

 var cert = psv_get_valid_cert();
 if(!cert){
   cert = psv_get_invalid_cert();  
 }

 if(!cert) {
   return null;
 }
 return(cert.md5Fingerprint);
} 

/* Takes an SslCert Returns a Notary Response*/
function queryNotaries(cert){

  /* We hate pnc bank! */
  if(cert.host.match(/pnc/)){
    return new NotaryResponse(0,0);
  }

  return new NotaryResponse(3, 10);
}

function applyPolicy(cert){

  resp = queryNotaries(cert);
  cert.quorum   = resp.quorum;
  cert.duration = resp.duration;

  if(resp.quorum < 3){
    cert.secure = false;
  }
  else{
    cert.secure = true;
  }
  return cert;
}
  
function do_override() { 
  var gSSLStatus = get_invalid_cert_SSLStatus();
  if(!gSSLStatus){ //this paged loaded properly so don't do anythign
    return false;
  }
  var cert = cert_from_SSLStatus(gSSLStatus);
  if(!cert){
    return;
  }

	var uri = gBrowser.currentURI;  
	var overrideService = Components.classes["@mozilla.org/security/certoverride;1"]
		.getService(Components.interfaces.nsICertOverrideService);

  var flags = 0;
  if(gSSLStatus.isUntrusted)
    flags |= overrideService.ERROR_UNTRUSTED;
  if(gSSLStatus.isDomainMismatch)
    flags |= overrideService.ERROR_MISMATCH;
  if(gSSLStatus.isNotValidAtThisTime)
    flags |= overrideService.ERROR_TIME;

	overrideService.rememberValidityOverride(
			uri.asciiHost, uri.port,
			cert,
			flags,
			true);
 
	gBrowser.reload(); 
  return true;
} 

function isConsistent(notaryResp){
  return true;
}

function setStatusSecure(){
  dump("Secure Status\n");
  document.getElementById("perspective-status-image")
    .setAttribute("hidden", "false");
  document.getElementById("perspective-status-image")
    .setAttribute("src", "chrome://perspectives/content/good.png");
  do_override();
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
function updateStatus(location){

  if(!location || location.scheme != "https"){
    setStatusNeutral();
    return;
  }
  dump("update ");
  dump(location.spec);
  dump("\n");

  var md5 = getFingerprint();
  if(!md5){
    dump("Couldn't find md5 the page hasn't finished loading\n");
    return;
  }

  dump("check cache(");
  dump(ssl_cache[location.host]);
  dump(")\n");

  if(!ssl_cache[location.host] || ssl_cache[location.host].md5 != md5){
    var tmp = new SslCert(location.host, location.port, md5, false);
    ssl_cache[location.host] = applyPolicy(tmp);
  }

  cache_cert = ssl_cache[location.host];

  if(cache_cert.secure){
    setStatusSecure();
  }
  else{
    setStatusUnsecure();
  }
}

var notaryListener = { 
	/* If something changes in the locationation bar */
	onLocationChange: function(webProgress, request, location) {
    //dump("Location changed to " + location.scheme + "\n");
    updateStatus(location);
		return;
	},

	onStateChange: function(webProgress, request, stateFlags, status) {
		return;
	},

	onProgressChange: function(webProgress, request, curSelfProgress, 
    maxSelfProgress, curTotalProgress, maxTotalProgress) {
   if (curTotalProgress >= maxTotalProgress){
      updateStatus(getBrowser().currentURI);
    }
		return;
	},

	onSecurityChange: function(webProgress, request, state) {
		return;
	},

	onStatusChange: function(webProgress, request, status, message) {
		return;
	},

	onLinkIconAvailable: function() {
		return;
	}
};

function initNotaries(){
  getBrowser().addProgressListener(notaryListener, 
    Components.interfaces.nsIWebProgress.NOTIFY_STATE_DOCUMENT);
}
