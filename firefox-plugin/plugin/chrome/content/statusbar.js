var root_prefs = Components.classes["@mozilla.org/preferences-service;1"]
                 .getService(Components.interfaces.nsIPrefBranchInternal);

var valid_state = false;

var ProgressListener = {
	/* If something changes in the location bar */
	onLocationChange: function(webProgress, request, location) {

		if (!location)
			return;
                
                dump("Scheme is " + location.scheme + "\n");

		if (location.scheme == 'file' || location.scheme == 'chrome' || location.scheme == 'about')
			return;

		/* If there are some more schemes that do not support a host */
		try {
			if (!location.host)
				return;
		} catch(ex) {
			return;
		}

                if(!valid_state)
                {    
                    root_prefs.setCharPref("perspectives.info", "N/A");
                }
                else
                {
                    valid_state = false;
                }

		return;
	},

	onStateChange: function(webProgress, request, stateFlags, status) {
		return;
	},

	onProgressChange: function(webProgress, request, curSelfProgress, maxSelfProgress, curTotalProgress, maxTotalProgress) {
		return;
	},

	onSecurityChange: function(webProgress, request, state) {
		return;
	},

	onStatusChange: function(webProgress, request, status, message) {
		return;
	},

	onLinkIconAvailable: function() {
		return;
	}
};



function StatusDisplay(label, tooltip) {
        dump("Displaying " + label + " \n");
	var display = document.getElementById("perspective-statusbar-label");
	if (!display)
            return;

	if (label.length == 0)
            label = "N/A";

	display.setAttribute("value", label);

	var tt = document.getElementById("perspective-status-tooltip");
	if (tt != null) {
            while(tt.hasChildNodes())
                tt.removeChild(tt.firstChild);
	}

	var node = null;
        if (tooltip.length == 0)
            tooltip = "N/A";

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


function ShowInfo() {
        dump("Show Info\n");
	window.openDialog("chrome://perspectives/content/statusbar-info.xul", "perspectiveInfo", "centerscreen,modal").focus();
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
    var config = "file://" + config_path + "/" + "client_config.txt";
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
        
            
      dump("Info Changed: "  + "\n");        
      var image = document.getElementById("perspective-status-image");
      if(this._branch.getCharPref("perspectives.info") !=  "N/A")
      {

          try{
              if(root_prefs.getBoolPref("perspectives.status") == true )
              {
                  image.setAttribute("hidden", "false");
                  image.setAttribute("src", "chrome://perspectives/content/good.png");
                  StatusDisplay("Notarized", "Perspectives Notarized");
              }    
              else
              {
                  if(root_prefs.getIntPref("perspectives.secpref") != 2 )
                  {
                    alert("Notaries donot agree to this Key. Denied Access");
                  }
                  else
                  {
                    alert("Notaries donot agree to this Key. It is advisable to verify the key manually");
                  }
                  image.setAttribute("hidden", "false");
                  image.setAttribute("src", "chrome://perspectives/content/bad.png");
                  StatusDisplay("Veto-ed", "Perspectives Veto-ed");
              }    
          }
          catch(ex)
          {
              image.setAttribute("hidden", "true");
              StatusDisplay("N/A", "Not Applicable");
          }
          valid_state = true;
      }    
      else
      {
          image.setAttribute("hidden", "true");
          StatusDisplay("N/A", "Not Applicable");
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
    /* Progress Listener */
    window.getBrowser().addProgressListener(ProgressListener, Components.interfaces.nsIWebProgress.NOTIFY_LOCATION | Components.interfaces.nsIWebProgress.NOTIFY_STATE_DOCUMENT);
}

function evtUnload(evt)
{
   myPrefObserver.unregister();
}

