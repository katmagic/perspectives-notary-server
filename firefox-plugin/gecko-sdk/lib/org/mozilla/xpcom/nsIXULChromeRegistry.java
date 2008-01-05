/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIXULChromeRegistr">
 **/

package org.mozilla.xpcom;

public interface nsIXULChromeRegistry extends nsIChromeRegistry
{
  public static final String NS_IXULCHROMEREGISTRY_IID =
    "{3e51f40b-b4b0-4e60-ac45-6c63477ebe41}";

  public void reloadChrome();

  public String getSelectedLocale(String arg1);

  public void refreshSkins();

  public boolean allowScriptsForPackage(nsIURI arg1);

}
