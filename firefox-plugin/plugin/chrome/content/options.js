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
                 dump("High Security\n");
                 display1.setAttribute("value", "High Security Preference");
                 display2.setAttribute("value", "Accept a key when 75% of all notary servers have");
                 display3.setAttribute("value", "seen only that key for the past 3 days.");

                 break;
        case 1:
                 dump("Moderate Security\n");       
                 display1.setAttribute("value", "Moderate Security Preference");
                 display2.setAttribute("value", "Accept a key when 75% of all notary servers"); 
                 display3.setAttribute("value", "report that key as the current key.");

                 break;

        case 2:
                 dump("High Availability\n");       
                 display1.setAttribute("value", "High Availability Preference (experts only)");
                 display2.setAttribute("value", "Same as moderate security, but user will be able to");
                 display3.setAttribute("value", "override key-trust decision manually.");
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
   
    config_path = config_path + "/notary_list.txt";
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
