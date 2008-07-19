var root_prefs = Components.classes["@mozilla.org/preferences-service;1"].
getService(Components.interfaces.nsIPrefBranch);

var browser;


function setDuration(flt){
  root_prefs.setIntPref("perspectives.required_duration", 100 * flt);
}

function setQuorum(num){
   /* if(!typeof(num)=="number"){
      num = parseInt(num);
    }*/
    if(num < 0){
      num = 0;
      document.getElementById("pref-thresh").value="0"
    }
    else if(num > 100){
      num = 100;
      document.getElementById("pref-thresh").value="100"
    }
    root_prefs.setIntPref("perspectives.quorum_thresh", num);
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
    quorum.readOnly   = true;

    duration.value    = du;
    duration.readOnly = true;

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
      quorum.readOnly   = false;
      duration.readOnly = false;
      break;
  }

}

/* Update the xul */
function setInformation(info){

  var display = document.getElementById("perspective-statusinfo-description");
  if (!display){
    dump("Null Display \n");
    return;
  }

  if (info.length == 0){
    info  = "Nothing!";
  }
  display.setAttribute("value", info);
}

function setQuorumDuration(text){
  var line = document.getElementById("perspective-quorum-duration");
  if (!line){
    dump("couldn't find quorum duration line \n");
    return;
  }
  line.setAttribute("value", text);
}

function LoadInfo(brws, ssl_cache){
  browser = brws;
 
  selectSecurity();
  /* Set the notary result information */
  var cert = ssl_cache[browser.currentURI.host];
  if(!cert){
    setQuorumDuration("No Quorum Information");
    setInformation("This site does not use ssl encryption");
    return;
  }

  if(!cert.secure){
    setQuorumDuration("Invalid Certificate\n");
  }
  else{
    setQuorumDuration("Valid Certificate with duration: " 
        + cert.duration + "\n");
  }

  setInformation(cert.summary);

  return true;
}

function dialogAccept(){
  return true;
}

//Should open new window because the dialog prevents them from seeing it
function openNotaries(){
  window.open("chrome://perspectives_main/content/notary_list.txt");

}

function onHelp(){
  window.open("chrome://perspectives_main/content/help.html");
}


