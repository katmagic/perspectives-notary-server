const __doOK = doOK;
const __onLoad = onLoad;
const root_prefs = Components.classes["@mozilla.org/preferences-service;1"].
                    getService(Components.interfaces.nsIPrefBranch);

onLoad = function() {

    dump("In OnLoad of the warn box \n");
    var currentValue = root_prefs.getBoolPref("perspectives.show_warn");
    if(currentValue)
    {
        var display = document.getElementById("warning-label");
        if (!display)
        {
            dump("Null Display \n");
            __onLoad();
            return;
        }
        display.setAttribute( "value", "The Notary Servers do not agree with the Certificate.");
        root_prefs.setBoolPref("perspectives.show_warn", false);
    }
    dump("Calling __onLoad() \n");
    __onLoad();
}


doOK = function(){
    
    dump("Calling __doOK() \n");
    __doOK(); // call chrome://pippki/content/domainMismatch.js doOK()
              // *or* chrome://pippki/content/serverCertExpired.js doOK()
}


