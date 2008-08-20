var root_prefs = Components.classes["@mozilla.org/preferences-service;1"]
.getService(Components.interfaces.nsIPrefBranchInternal);

function ShowInfo(ssl_cache,other_cache) {
  window.openDialog("chrome://perspectives/content/statusbar-info.xul", 
      "perspectiveInfo", "centerscreen, chrome, toolbar", gBrowser, ssl_cache,other_cache).focus();
}

function evtLoad(evt){
  initNotaries();
  if(!root_prefs.getBoolPref("perspectives.show_label")){
    document.getElementById("perspective-statusbar-label").hidden =
      true;
  }
}

window.addEventListener('load',evtLoad,false);
