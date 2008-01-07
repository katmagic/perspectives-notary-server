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
    var display1 = document.getElementById("perspective-secpref-description1");
    var display2 = document.getElementById("perspective-secpref-description2");
    var display3 = document.getElementById("perspective-secpref-description3");
    if (!display1 || !display2 || !display3)
    {
        dump("Null Display \n");
        return;
    }

    switch(index)
    {
        case 0:
                 dump("High\n");
                 display1.setAttribute("value", "High Security Preference");
                 display2.setAttribute("value", "-Expects 75% of notary server to agree.");
                 display3.setAttribute("value", "-Expects a quorum duration of 3 days.");

                 break;
        case 1:
                 dump("Medium\n");       
                 display1.setAttribute("value", "Medium Security Preference");
                 display2.setAttribute("value", "-Expects 75% of notary server to agree.");
                 display3.setAttribute("value", "-Expects the keys to be currently consistent.");
                 break;

        case 2:
                 dump("Low\n");       
                 display1.setAttribute("value", "Low Security Preference");
                 display2.setAttribute("value", "-This is High Availability Profile.");
                 display3.setAttribute("value", "-To be used by expert users only.");
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
