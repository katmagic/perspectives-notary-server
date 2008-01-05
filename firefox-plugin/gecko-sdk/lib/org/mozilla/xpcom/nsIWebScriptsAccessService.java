/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIWebScriptsAccess">
 **/

package org.mozilla.xpcom;

public interface nsIWebScriptsAccessService extends nsISupports
{
  public static final String NS_IWEBSCRIPTSACCESSSERVICE_IID =
    "{57e2860b-4266-4a85-bfde-ae39d945b014}";

  public boolean canAccess(nsIURI arg1, String arg2);

  public void invalidateCache(String arg1);

}
