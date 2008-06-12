var root_prefs = Components.classes["@mozilla.org/preferences-service;1"]
.getService(Components.interfaces.nsIPrefBranchInternal);

var valid_state = false;

/* We are going to cache the results (e.g which keys were accepted
 * in an object using it as an "associative array"  I don't really know 
 * if this is good form but It seems to be prevalant enough */
function StatusDisplay(label, tooltip) {
  dump("Displaying " + label + " \n");
  var display = document.getElementById("perspective-statusbar-label");
  if (!display)
    return;

  display.setAttribute("value", label);

  var tt = document.getElementById("perspective-status-tooltip");
  if (tt != null) {
    while(tt.hasChildNodes())
      tt.removeChild(tt.firstChild);
  }

  var node = null;

  node = document.createElement("label");
  node.setAttribute("value", tooltip);
  tt.appendChild(node);

  return;
}


function ShowContextMenu(e) {
  dump("Show Context Menu\n");
  var statusbar = document.getElementById("perspective-status");
  var context = document.getElementById("perspective-contextmenu");
  var x = e.clientX;
  var y = e.clientY;
  document.popupNode = statusbar;
  context.showPopup(statusbar, x, y, "bottomleft", "topleft");
}


function ShowInfo(ssl_cache) {
  dump("Show Info\n");
  window.openDialog("chrome://perspectives/content/statusbar-info.xul", 
    "perspectiveInfo", "centerscreen,modal", gBrowser, ssl_cache).focus();
}


function ViewConfig() {

  var config_path;
  try
  {
    config_path = root_prefs.getCharPref("perspectives.ext_dir");
  }
  catch(ex)
  {
    var psv = Components.classes["@cmu.edu/psvBadCertHandler;1"]
      .getService(Components.interfaces.psvIBadCertHandler);
    psv.setExtDir();                  
    config_path = root_prefs.getCharPref("perspectives.ext_dir");
  }    
  var config = "file://" + config_path + "/" + "notary_list.txt";
  dialog = window.openDialog(config, "perspectiveConfig", "centerscreen,modal", config).focus();
}

function ViewPreferences()
{
  dialog = window.openDialog("chrome://perspectives/content/options2.xul", "PerspectivePreferences", "centerscreen,modal").focus();

}

var myPrefObserver =
{
register: function()
          {
            var observingPrefsActive = false;
            var prefService = Components.classes["@mozilla.org/preferences-service;1"]
              .getService(Components.interfaces.nsIPrefBranchInternal);
            this._branch = prefService.QueryInterface(Components.interfaces.nsIPrefBranchInternal);
            this._branch.addObserver("", this, false);
            this._branch.setCharPref("perspectives.info", "N/A");
            this._branch.setBoolPref("perspectives.show_warn", false); // Move this to appropriate place
            this._branch.setBoolPref("perspectives.status", false); // Move this to appropriate place
          },

unregister: function()
            {
              if(!this._branch) return;
              this._branch.removeObserver("", this);
            },

observe: function(aSubject, aTopic, aData)
         {
           if(aTopic != "nsPref:changed") return;
           // aSubject is the nsIPrefBranch we're observing
           // aData is the name of the pref that's been changed (relative to aSubject)
           switch (aData) {
             case "perspectives.info":

               dump("Info/QD Changed: "  + "\n");        
             var image = document.getElementById("perspective-status-image");

             if(this._branch.getCharPref("perspectives.info") !=  "N/A")
             {
               var qd_days = this._branch.getCharPref("perspectives.quorum_duration"); 
               var is_consistent = this._branch.getBoolPref("perspectives.is_consistent");
               var mouseover_text = ""; 
               if(is_consistent) { 
                 mouseover_text = "Key is consistent (quorum-duration = " + qd_days + " days)."; 
               } else { 
                 mouseover_text = "Key is NOT consistently seen by notary."; 
               }

               try{
                 if(root_prefs.getBoolPref("perspectives.status") == true )
                 {
                   image.setAttribute("hidden", "false");
                   image.setAttribute("src", "chrome://perspectives/content/good.png");
                   StatusDisplay("Key Verified", mouseover_text);
                 }    
                 else
                 {
                   if(root_prefs.getIntPref("perspectives.secpref") != 2 )
                   {
                     alert("Notaries do not agree to this Key. Denied Access");
                   }
                   else
                   {
                     alert("Notaries do not agree to this Key. It is advisable to verify the key manually");
                   }
                   image.setAttribute("hidden", "false");
                   image.setAttribute("src", "chrome://perspectives/content/bad.png");
                   StatusDisplay("Key Unverified", mouseover_text);
                 }    
               }
               catch(ex)
               {
                 image.setAttribute("hidden", "true");
                 StatusDisplay("", "No notaries were contacted for this site.");
               }
               valid_state = true;
             }    
             else
             {
               image.setAttribute("hidden", "true");
               StatusDisplay("", "No notaries were contacted for this site");
             }
             break;
           }
         }
}

window.addEventListener('load',evtLoad,false);
window.addEventListener('unload',evtUnload,false);

function evtLoad(evt)
{
  myPrefObserver.register();
  initNotaries();
}

function evtUnload(evt)
{
  myPrefObserver.unregister();
}

