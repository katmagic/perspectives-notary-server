var root_prefs = Components.classes["@mozilla.org/preferences-service;1"].
                      getService(Components.interfaces.nsIPrefBranch);

function getQuorumThresh(){
  try{
    return root_prefs.getIntPref("perspectives.quorum_thresh");
  }
  catch (e){
    setQuorumThresh(3); //default quorum thresh
    return root_prefs.getIntPref("perspectives.quorum_thresh");
  }
}

function setQuorumThresh(thresh){
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

function LoadInfo(browser, ssl_cache){

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

  //Set the quorum thresh
  var line = document.getElementById("perspective-quorum-thresh");
  line.setAttribute("value", getQuorumThresh());

	return true;
}

function dialogAccept(){
  var line = document.getElementById("perspective-quorum-thresh");
  if(line.value < 1){
    return true;
  }
  setQuorumThresh(parseInt(line.value));
  return true;
}

