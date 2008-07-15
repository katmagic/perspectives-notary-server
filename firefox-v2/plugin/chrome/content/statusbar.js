var root_prefs = Components.classes["@mozilla.org/preferences-service;1"]
.getService(Components.interfaces.nsIPrefBranchInternal);

function ShowInfo(ssl_cache) {
  window.openDialog("chrome://perspectives/content/statusbar-info.xul", 
      "perspectiveInfo", "centerscreen,modal", gBrowser, ssl_cache).focus();
}

function evtLoad(evt){
  initNotaries();
}
window.addEventListener('load',evtLoad,false);
