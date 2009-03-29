var root_prefs = Components.classes["@mozilla.org/preferences-service;1"].
getService(Components.interfaces.nsIPrefBranch);
//const XUL_NS = "http://www.mozilla.org/keymaster/gatekeeper/there.is.only.xul";

var browser;

function openCertificates(){
  openDialog("chrome://pippki/content/certManager.xul", "Certificate Manager");
}

function setDuration(flt){
  root_prefs.setIntPref("perspectives.required_duration", 100 * flt);
  clear_cache();
}

function setQuorum(num){
  if(num < 0){
    num = 0;
    document.getElementById("pref-thresh").value="0"
  }
  else if(num > 100){
    num = 100;
    document.getElementById("pref-thresh").value="100"
  }
  root_prefs.setIntPref("perspectives.quorum_thresh", num);
  clear_cache();
}

function setManual(){
  document.getElementById("secset").value = -1;
  root_prefs.setIntPref("perspectives.security_settings", -1);
}

function selectSecurity(){
  var d = document;
  var setting  = d.getElementById("secset").value;
  var quorum   = d.getElementById("pref-thresh");
  var duration = d.getElementById("pref-duration");

  quorum.value   = root_prefs.getIntPref("perspectives.quorum_thresh");
  duration.value = 
    root_prefs.getIntPref("perspectives.required_duration") / 100.0;

  function menuset(qu, du){
    quorum.value      = qu;
    duration.value    = du;

    setQuorum(qu);
    setDuration(du);
  }
  
  switch (parseInt(setting)){
    case 2:
      menuset(75, 2);
      break;
    case 1:
      menuset(75, 0);
      break;
    case 0:
      menuset(50, 0);
      break;
    case -1:
      break;
  }
}

//Should open new window because the dialog prevents them from seeing it
function openNotaries(){
  openDialog("chrome://perspectives_main/content/notary_list.txt", 
		"", "width=600,height=600,resizable=yes");
}

function onHelp(){
  openDialog("chrome://perspectives_main/content/help.html","",
		"width=600,height=600,resizable=yes");
}

function switchResultForm(){
  var sel = document.getElementById("info-radio").selectedIndex;
  document.getElementById("perspective-svg-box").hidden     = sel;
  document.getElementById("perspective-description").hidden = !sel;
}

function requery(){
  requeryAllTabs(browser);
}

function addTimeline(svgString){
  parser       = new DOMParser();
  var svgDoc   = parser.parseFromString(svgString, "text/xml");
  var elements = svgDoc.getElementsByTagName("svg");
  var svg      = elements[0];
  var after    = document.getElementById("perspective-svg-box");
  after.appendChild(svg);
}

// returns a string that describes whether perspectives installed a security exception 
function getActionStr(ti) { 
 if(ti.is_override_cert && ti.already_trusted) 
   return  "Perspectives has previously installed a security exception for this site."; 
 if(ti.already_trusted) 
   return "The browser trusts this site and requires no security exception";  
 if(ti.is_override_cert && ti.notary_valid && ti.exceptions_enabled && ti.isTemp) 
   return  "Perspectives installed a temporary security exception for this site."; 
 if(ti.is_override_cert && ti.notary_valid && ti.exceptions_enabled && !ti.isTemp)  
   return "Perspectives installed a permanent security exception for this site."; 
 return "No security exception has been installed"; 
}

function LoadInfo(brws, ssl_cache, other_cache,tab_info_cache){
  try { 
  	selectSecurity();
  	document.getElementById("perspective-debug").value = other_cache["debug"];
  	browser   = brws; // save as global
  
  	var info  = document.getElementById("perspective-description");
  	var liner = document.getElementById("perspective-quorum-duration");
  	var host  = document.getElementById("perspective-information-caption");
  	if(!brws || !brws.currentURI) 
		return; 
 
  	var uri = brws.currentURI; 
  	var cert  = ssl_cache[uri.host];
        var ti = tab_info_cache[uri.spec]; 
  	host.label = uri.host;
	if(ti) { 
		host.label += ": " + getActionStr(ti); 
	} 
  	if(cert){
    		info.value  = cert.summary;
    		liner.value = cert.tooltip;
    		if(cert.svg && cert.svg != ""){
      			info.hidden = true;
      			addTimeline(cert.svg);
      			var radio = document.getElementById("info-radio");
      			radio.hidden=false;
      			radio.selectedIndex = 0;
    		}
  	} else if (other_cache["reason"]) {
    		info.value = other_cache["reason"]; 
  	} 
  } catch(e) { 
	alert("Error loading Perspectives dialog: " + e); 
  } 
  return true;
}

