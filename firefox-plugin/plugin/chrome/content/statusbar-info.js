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

function setQuorumDuration(text)
{

    var line = document.getElementById("perspective-quorum-duration");
    if (!line)
    {
        dump("couldn't find quorum duration line \n");
        return;
    }

    line.setAttribute("value", text);
    dump("Set quorum-duration line: " + text);

}

function LoadInfo() {
        dump("Load Info\n");
        var currentValue = root_prefs.getCharPref("perspectives.info");

        setInformation(currentValue);

        var qd_days = root_prefs.getCharPref("perspectives.quorum_duration");
        var is_consistent = root_prefs.getBoolPref("perspectives.is_consistent");
        if(is_consistent) 
          setQuorumDuration("The key is consistent with a quorum-duration of " + qd_days + " days");
        else
          setQuorumDuration("The key is INCONSISTENT.\n"); 

	return true;
}

