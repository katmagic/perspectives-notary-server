var root_prefs = Components.classes["@mozilla.org/preferences-service;1"].
getService(Components.interfaces.nsIPrefBranch);

var browser;

function getQuorumThresh(){
  try{
    return root_prefs.getIntPref("perspectives.quorum_thresh");
  }
  catch (e){
    setQuorumThresh(75); //default quorum thresh
    return root_prefs.getIntPref("perspectives.quorum_thresh");
  }
}

function setQuorumThresh(thresh){
  if(thresh < 0 || thresh > 100){
    alert("The quorum thresh is a percentage and should be between 0 and 100");
    return false;
  }
  root_prefs.setIntPref("perspectives.quorum_thresh", thresh);
  return true;
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
  dump("Set Information " + info + "\n");
}

function setQuorumDuration(text){
  var line = document.getElementById("perspective-quorum-duration");
  if (!line){
    dump("couldn't find quorum duration line \n");
    return;
  }
  line.setAttribute("value", text);
  dump("Set quorum-duration line: " + text + "\n");
}

function LoadInfo(brws, ssl_cache){

  browser = brws;
  //Set the quorum thresh
  var line = document.getElementById("perspective-quorum-thresh");
  line.setAttribute("value", getQuorumThresh());

  /* Later we will pass the md5 into here*/
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
  var line = document.getElementById("perspective-quorum-thresh");
  opener.clear_cache();
  return setQuorumThresh(parseInt(line.value));
}

function openNotaries(){
  browser.loadOneTab("chrome://perspectives_main/content/notary_list.txt",
      null, null, null, false);
}

function onHelp(){
  browser.loadOneTab("chrome://perspectives_main/content/help.html",
      null, null, null, false);
}


