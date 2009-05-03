var root_prefs = Components.classes["@mozilla.org/preferences-service;1"].getService(Components.interfaces.nsIPrefBranch);

function disable_quorum_text(is_disabled) { 
  document.getElementById("quorum-thresh-text").disabled=is_disabled;
  document.getElementById("quorum-duration-text").disabled=is_disabled; 
} 

function menuset(qu, du){
    disable_quorum_text(true); 
    document.getElementById("quorum-thresh").value = qu;
    document.getElementById("quorum-duration").value = du;
}

function security_class_change() { 
  var setting  = document.getElementById("secset").value;

  switch (parseInt(setting)){
    case 2:
      menuset(75, 2);
      break;
    case 1:
      menuset(75, 0);
      break;
    case 0:
      menuset(50, 0);
      break;
    case -1:
      disable_quorum_text(false); 
      break;
  }

} 
  
function load_preferences(){
	security_class_change();  
}


