const CLASS_ID = Components.ID("{0c4695a0-b6a6-11dc-8314-0800200c9a66}");
const CLASS_NAME = "PSV";
const CONTRACT_ID = "@cmu.edu/psvBadCertHandler;1";


var root_prefs = Components.classes["@mozilla.org/preferences-service;1"].
                      getService(Components.interfaces.nsIPrefBranch);



/** class **/
function psvBadCertHandler() { };
psvBadCertHandler.prototype = {

    setExtDir: function(){
        var componentFile = __LOCATION__;
        var componentsDir = componentFile.parent;
        var extensionDir = componentsDir.parent
            var path = extensionDir.path
            dump("Extension Dir is " + path + "\n")
	alert("in JS setExtDir"); ;
        root_prefs.setCharPref("perspectives.ext_dir", path);
        return true;
    },

    confirmMismatchDomain: function(socketInfo, targetURL, cert) {
	var certpick = Components.classes["@mozilla.org/nsCertPickDialogs;1"]
                            .getService(Components.interfaces.nsIBadCertListener);

        dump("Domain Mismatch \n");


	return certpick.confirmMismatchDomain(socketInfo, targetURL, cert);
    },

    confirmCertExpired: function(socketInfo, cert) {
	var certpick = Components.classes["@mozilla.org/nsCertPickDialogs;1"]
                            .getService(Components.interfaces.nsIBadCertListener);
        dump("Cert Expired \n");
        
        root_prefs.setBoolPref("perspectives.show_warn", true);

	return certpick.confirmCertExpired(socketInfo, cert);
    },

    confirmUnknownIssuer: function(socketInfo, cert, certAddType) {
	var certpick = Components.classes["@mozilla.org/nsCertPickDialogs;1"]
                            .getService(Components.interfaces.nsIBadCertListener);
        dump("Unknown Issuer " + certAddType + "\n");
        return certpick.confirmUnknownIssuer(socketInfo, cert, certAddType);
    },

    notifyCrlNextupdate: function(socketInfo, targetURL, cert) {
	var certpick = Components.classes["@mozilla.org/nsCertPickDialogs;1"]
                            .getService(Components.interfaces.nsIBadCertListener);
        dump("CRL Next Update \n");
	return certpick.notifyCrlNextupdate(socketInfo, targetURL, cert);
    },

    QueryInterface: function(aIID)  {
        if (!aIID.equals(Components.interfaces.psvIBadCertHandler) &&
            !aIID.equals(Components.interfaces.nsISupports)) {
                throw Components.results.NS_ERROR_NO_INTERFACE;
        } else {
            return this;
        }
    },
};

/** class factory **/
var psvBadCertHandlerFactory = {
  createInstance: function (aOuter, aIID)  {
    if (aOuter != null)
      throw Components.results.NS_ERROR_NO_AGGREGATION;
    return (new psvBadCertHandler()).QueryInterface(aIID);
  }
};

/** module defined - xpcom registration **/
var psvBadCertHandlerModule = {
  _firstTime: true,
  registerSelf: function(aCompMgr, aFileSpec, aLocation, aType)  {
    aCompMgr = aCompMgr.QueryInterface(Components.interfaces.nsIComponentRegistrar);
    aCompMgr.registerFactoryLocation(CLASS_ID, CLASS_NAME, CONTRACT_ID, aFileSpec, aLocation, aType);
  },

  unregisterSelf: function(aCompMgr, aLocation, aType) {
    aCompMgr = aCompMgr.QueryInterface(Components.interfaces.nsIComponentRegistrar);
    aCompMgr.unregisterFactoryLocation(CLASS_ID, aLocation);
  },

  getClassObject: function(aCompMgr, aCID, aIID)  {
    if (!aIID.equals(Components.interfaces.nsIFactory))
      throw Components.results.NS_ERROR_NOT_IMPLEMENTED;

    if (aCID.equals(CLASS_ID))
      return psvBadCertHandlerFactory;
    throw Components.results.NS_ERROR_NO_INTERFACE;
  },

  canUnload: function(aCompMgr) { return true; }
};

/** module init **/
function NSGetModule(aCompMgr, aFileSpec) 
{ 

    return psvBadCertHandlerModule; 
}
