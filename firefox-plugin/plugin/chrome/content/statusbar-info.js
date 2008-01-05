var root_prefs = Components.classes["@mozilla.org/preferences-service;1"].
                      getService(Components.interfaces.nsIPrefBranch);

function setInformation(info)
{

    var display = document.getElementById("perspective-statusinfo-description");
    if (!display)
    {
        dump("Null Display \n");
        return;
    }

    if (info.length == 0)
        info  = "Nothing!";
    display.setAttribute("value", info);
    dump("Set Information " + info);

}

function LoadInfo() {
        dump("Load Info\n");
        var currentValue = root_prefs.getCharPref("perspectives.info");

        setInformation(currentValue);


	return true;
}

