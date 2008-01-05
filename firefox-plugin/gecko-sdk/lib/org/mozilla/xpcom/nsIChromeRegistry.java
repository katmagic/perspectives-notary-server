/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIChromeRegistry">
 **/

package org.mozilla.xpcom;

public interface nsIChromeRegistry extends nsISupports
{
  public static final String NS_ICHROMEREGISTRY_IID =
    "{68389281-f6d0-4533-841d-344a2018140c}";

  public static final int NONE = 0;

  public static final int PARTIAL = 1;

  public static final int FULL = 2;

  public nsIURI convertChromeURL(nsIURI arg1);

  public void checkForNewChrome();

}
