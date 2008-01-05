const root_prefs = Components.classes["@mozilla.org/preferences-service;1"].
                    getService(Components.interfaces.nsIPrefBranch);



function displayInfo()
{
    var index;
    try {
        index = root_prefs.getIntPref("perspectives.secpref");
        document.getElementById('perspective-secpref-radiogroup').selectedIndex = index;
    }
    catch(ex)
    {
        index = document.getElementById('perspective-secpref-radiogroup').selectedIndex;
    }
    chooseType(index);

}

function chooseType(index)
{
    var display = document.getElementById("perspective-secpref-description");
    if (!display)
    {
        dump("Null Display \n");
        return;
    }

    switch(index)
    {
        case 0:
                 dump("High\n");
                 display.setAttribute("value", "High Security Preference -Expects all notary servers to agree");

                 break;
        case 1:
                 dump("Medium\n");       
                 display.setAttribute("value", "Medium Security Preference - Warns you before allowing you to connect.");
                 break;

        case 2:
                 dump("Low\n");       
                 display.setAttribute("value", "Low Security Preference - Allows to connect if notaries agree recent key");
                 break;
    }
    root_prefs.setIntPref("perspectives.secpref", index);

}
function onload(){
    
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
    
    if (config_path.length == 0)
        return;
   
    config_path = config_path + "/client_config.txt";
    var display = document.getElementById("perspective-confpath-label");
    if (!display)
    {
        dump("Null Display \n");
        return;
    }

    display.setAttribute("value", config_path);

    displayInfo();

    return;
}

function ok()
{
    dump("OK\n");
    window.close();
}
