const STATE_ERROR   = -1;
const STATE_SEC   = 0;
const STATE_NSEC  = 1;
const STATE_NEUT  = 2;
const STATE_START = Components.interfaces.nsIWebProgressListener.STATE_START;
const STATE_STOP  = Components.interfaces.nsIWebProgressListener.STATE_STOP;

function statusbar_click(event) {
	d_print("main",event); 
	d_print("main", event.button); 
	open_results_dialog();
} 

// note: when debugging, it is useful to open this dialog as a 
// window, so we get a firebug console, etc
function open_results_dialog() { 
 	window.openDialog(
 //	window.open( // for debug
		"chrome://perspectives/content/results_dialog.xul", 
//        	"perspectivesResults", "").focus();  // for debug
		"perspectivesresults", "centerscreen, chrome, toolbar").focus();

} 

// note: when debugging, it is useful to open this dialog as a 
// window, so we get a firebug console, etc
function open_preferences_dialog() { 
 	window.openDialog(
// 	window.open( // for debug
		"chrome://perspectives/content/preferences_dialog.xul", 
//       	"perspectivesResults", "").focus();  // for debug
		"perspectivesresults", "centerscreen, chrome, toolbar").focus();

} 


function setStatus(uri,state, tooltip){
  if(uri != null && uri != window.gBrowser.currentURI) { 
//	d_print("main", "Ignoring setStatus for '" + uri.spec + 
//	"' because current browser tab is for '" + 
//	window.gBrowser.currentURI.spec + "'"); 
	return;  
  }
  if(!tooltip){
    tooltip = "Perspectives";
  }

  var i = document.getElementById("perspective-status-image");
  var t = document.getElementById("perspective-status");
  if(!t || !i){ //happens when called from a dialog
    i = window.opener.document.getElementById("perspective-status-image");
    t = window.opener.document.getElementById("perspective-status");
  }

  t.setAttribute("tooltiptext", tooltip);
  switch(state){
    case STATE_SEC:
      d_print("main", "Secure Status\n");
      i.setAttribute("src", "chrome://perspectives/content/good.png");
      break;
    case STATE_NSEC:
      d_print("main", "Unsecure Status\n");
      i.setAttribute("src", "chrome://perspectives/content/bad.png");
      break;
    case STATE_NEUT:
      d_print("main", "Neutral Status\n");
      i.setAttribute("src", "chrome://perspectives/content/default.png");
      break;
    case STATE_ERROR:
      d_print("main", "Error Status\n");
      i.setAttribute("src", "chrome://perspectives/content/error.png");
      break;
  }
  d_print("main", "changing tooltip to: " + tooltip + "\n"); 
  return true;
}

function openCertificates(){
  openDialog("chrome://pippki/content/certManager.xul", "Certificate Manager");
}

//Should open new window because the dialog prevents them from seeing it
function openNotaries(){
  openDialog("chrome://perspectives_main/content/http_notary_list.txt", 
		"", "width=600,height=600,resizable=yes");
}

function openHelp(){
  openDialog("chrome://perspectives_main/content/help.html","",
		"width=600,height=600,resizable=yes");
}

