
// gets current certificat, if it FAILED the security check 
function psv_get_invalid_cert() { 
  try {
    var recentCertsSvc = Components.classes["@mozilla.org/security/recentbadcerts;1"]
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

    return gSSLStatus.QueryInterface(Components.interfaces.nsISSLStatus).serverCert;
  }
  catch (e) {
    alert("exception: " + e); 
    return null;
  }

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

function Perspectives_GetFingerprint() { 

 var cert = psv_get_valid_cert();
 if(!cert)
   cert = psv_get_invalid_cert();  
 if(!cert) 
   alert("No certificate found for: " + gBrowser.currentURI); 
 else 
   alert(cert.md5Fingerprint);
} 


