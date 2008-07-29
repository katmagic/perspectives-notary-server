var root_prefs = Components.classes["@mozilla.org/preferences-service;1"].
getService(Components.interfaces.nsIPrefBranch);

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

function LoadInfo(brws, ssl_cache){
  var info  = document.getElementById("perspective-statusinfo-description");
  var liner = document.getElementById("perspective-quorum-duration");
  var cert  = ssl_cache[brws.currentURI.host];
 
  selectSecurity();
  info.setAttribute("value", cert.summary);
  liner.setAttribute("value", cert.tooltip);
  return true;
}

//Should open new window because the dialog prevents them from seeing it
function openNotaries(){
  window.open("chrome://perspectives_main/content/notary_list.txt");

}

function onHelp(){
  window.open("chrome://perspectives_main/content/help.html");
}


