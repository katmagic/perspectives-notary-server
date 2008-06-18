var root_prefs = Components.classes["@mozilla.org/preferences-service;1"].
                      getService(Components.interfaces.nsIPrefBranch);

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
  dump("Set Information " + info);
}

function setQuorumDuration(text){

  var line = document.getElementById("perspective-quorum-duration");
  if (!line){
    dump("couldn't find quorum duration line \n");
    return;
  }
  line.setAttribute("value", text);
  dump("Set quorum-duration line: " + text);
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
    setQuorumDuration("Valid Certificate\n");
  }

  var info = "Detailed Notary Response:\n" +
    "Host: "     + cert.host     + "\n" +
    "Quorum: "   + cert.quorum   + "\n" +
    "Duration: " + cert.duration + "\n" ;

  setInformation(info);
	return true;
}

