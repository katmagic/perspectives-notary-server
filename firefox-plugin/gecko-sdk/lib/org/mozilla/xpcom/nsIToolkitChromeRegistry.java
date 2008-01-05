/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIToolkitChromeReg">
 **/

package org.mozilla.xpcom;

public interface nsIToolkitChromeRegistry extends nsIXULChromeRegistry
{
  public static final String NS_ITOOLKITCHROMEREGISTRY_IID =
    "{94490b3f-f094-418e-b1b9-73878d29bff3}";

  public void processContentsManifest(nsIURI arg1, nsIURI arg2, nsIURI arg3, boolean arg4, boolean arg5);

  public void checkForOSAccessibility();

  public nsIUTF8StringEnumerator getLocalesForPackage(String arg1);

}
