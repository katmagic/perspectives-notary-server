var root_prefs = Components.classes["@mozilla.org/preferences-service;1"]
.getService(Components.interfaces.nsIPrefBranchInternal);

function ShowInfo(ssl_cache) {
  dump("Show Info\n");
  window.openDialog("chrome://perspectives/content/statusbar-info.xul", 
      "perspectiveInfo", "centerscreen,modal", gBrowser, ssl_cache).focus();
}


function ViewConfig() {
  var config_path;
  try{
    config_path = root_prefs.getCharPref("perspectives.ext_dir");
  }
  catch(ex){
    var psv = Components.classes["@cmu.edu/psvBadCertHandler;1"]
      .getService(Components.interfaces.psvIBadCertHandler);
    psv.setExtDir();                  
    config_path = root_prefs.getCharPref("perspectives.ext_dir");
  }    
  var config = "file://" + config_path + "/" + "notary_list.txt";
  dialog = window.openDialog(config, "perspectiveConfig", 
      "centerscreen,modal", config).focus();
}

function ViewPreferences() {
  dialog = window.openDialog("chrome://perspectives/content/options2.xul", 
      "PerspectivePreferences", "centerscreen,modal").focus();
}

window.addEventListener('load',evtLoad,false);
function evtLoad(evt){
  initNotaries();
}
