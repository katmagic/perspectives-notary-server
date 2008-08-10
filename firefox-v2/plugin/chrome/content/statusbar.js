var root_prefs = Components.classes["@mozilla.org/preferences-service;1"]
.getService(Components.interfaces.nsIPrefBranchInternal);

function ShowInfo(ssl_cache,other_cache) {
  window.openDialog("chrome://perspectives/content/statusbar-info.xul", 
      "perspectiveInfo", "centerscreen, chrome, toolbar", gBrowser, ssl_cache,other_cache).focus();
}

function evtLoad(evt){
  initNotaries();
}
window.addEventListener('load',evtLoad,false);
