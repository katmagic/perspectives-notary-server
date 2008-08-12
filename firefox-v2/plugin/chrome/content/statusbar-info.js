var root_prefs = Components.classes["@mozilla.org/preferences-service;1"].
getService(Components.interfaces.nsIPrefBranch);
const XUL_NS = "http://www.mozilla.org/keymaster/gatekeeper/there.is.only.xul";

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
  window.open("chrome://perspectives_main/content/notary_list.txt");
}

function onHelp(){
  window.open("chrome://perspectives_main/content/help.html");
}

function switchResultForm(){
  var sel = document.getElementById("info-radio").selectedIndex;
  document.getElementById("perspective-svg-box").hidden     = sel;
  document.getElementById("perspective-description").hidden = !sel;
}

function addTimeline(svgString){
  parser       = new DOMParser();
  var svgDoc   = parser.parseFromString(svgString, "text/xml");
  var elements = svgDoc.getElementsByTagName("svg");
  var svg      = elements[0];
  var after    = document.getElementById("perspective-svg-box");
  after.appendChild(svg);
}



function LoadInfo(brws, ssl_cache,other_cache){
  var info  = document.getElementById("perspective-description");
  var liner = document.getElementById("perspective-quorum-duration");
  var host  = document.getElementById("perspective-information-caption");
  var cert  = ssl_cache[brws.currentURI.host];
 
  host.label = brws.currentURI.host;
  selectSecurity();
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
  document.getElementById("perspective-debug").value = other_cache["debug"];
  
  return true;
}


