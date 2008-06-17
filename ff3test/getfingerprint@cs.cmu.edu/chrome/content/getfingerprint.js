
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


function do_override() { 

	var cert = psv_get_valid_cert();
	if(!cert)
		cert = psv_get_invalid_cert();  
	if(!cert) { 
		alert("No certificate found for: " + gBrowser.currentURI.host); 
		return; 
	} 

	var uri = gBrowser.currentURI;  
	var overrideService = Components.classes["@mozilla.org/security/certoverride;1"]
		.getService(Components.interfaces.nsICertOverrideService);
	var flags = 0;

//      Seems like the firefox code doesn't like all of these being set at once.  
//      we should look into this. 
	
	flags |= overrideService.ERROR_UNTRUSTED;
//	flags |= overrideService.ERROR_MISMATCH;
//	flags |= overrideService.ERROR_TIME;

	overrideService.rememberValidityOverride(
			uri.asciiHost, uri.port,
			cert,
			flags,
			false);
 
	gBrowser.reload(); 
} 


function run_perspectives() { 

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
   
   var il = man.getInstallLocation("getfingerprint@cs.cmu.edu");
   var dir = il.location; 
   dir.append("getfingerprint@cs.cmu.edu"); 

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
   var quorum_duration = root_prefs.getCharPref("perspectives.quorum_duration");
   var str = "Notary Lookup for:\n" + service_id + "\nwith key = " + cert.md5Fingerprint + "\n"; 
   str += "Results:\n"; 
   str += "Quorum duration = " + quorum_duration + " days\n"; 
   str += "is_consistent = " + is_consistent + "\n"; 
   str += "Notary Observations: \n" + info; 
   alert(str); 
 

 } catch (err) {
	 alert(err);
	 return;
 }
} 


