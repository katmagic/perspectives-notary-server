const STATE_ERROR   = -1;
const STATE_SEC   = 0;
const STATE_NSEC  = 1;
const STATE_NEUT  = 2;
const STATE_START = Components.interfaces.nsIWebProgressListener.STATE_START;
const STATE_STOP  = Components.interfaces.nsIWebProgressListener.STATE_STOP;

function ShowInfo(ssl_cache,other_cache) {
  window.openDialog("chrome://perspectives/content/statusbar-info.xul", 
    "perspectiveInfo", "centerscreen, chrome, toolbar", gBrowser, ssl_cache,other_cache).focus();
}

function setStatus(state, tooltip){
  if(!tooltip){
    tooltip = "Perspectives";
  }

  var i = document.getElementById("perspective-status-image");
  var t = document.getElementById("perspective-status");
  if(!t || !i){//appens when called from statusbar-info.js
    i = window.opener.document.getElementById("perspective-status-image");
    t = window.opener.document.getElementById("perspective-status");
  }

  t.setAttribute("tooltiptext", tooltip);
  switch(state){
    case STATE_SEC:
      d_print("Secure Status\n");
      i.setAttribute("src", "chrome://perspectives/content/good.png");
      break;
    case STATE_NSEC:
      d_print("Unsecure Status\n");
      i.setAttribute("src", "chrome://perspectives/content/bad.png");
      break;
    case STATE_NEUT:
      d_print("Neutral Status\n");
      i.setAttribute("src", "chrome://perspectives/content/default.png");
      break;
    case STATE_ERROR:
      d_print("Error Status\n");
      i.setAttribute("src", "chrome://perspectives/content/error.png");
      break;
  }
  d_print("changing tooltip to: " + tooltip + "\n"); 
  return true;
}
