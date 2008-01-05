/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIRefreshURI">
 **/

package org.mozilla.xpcom;

public interface nsIRefreshURI extends nsISupports
{
  public static final String NS_IREFRESHURI_IID =
    "{69efc430-2efe-11d2-9e5d-006008bf092e}";

  public void refreshURI(nsIURI arg1, int arg2, boolean arg3, boolean arg4);

  public void setupRefreshURI(nsIChannel arg1);

  public void setupRefreshURIFromHeader(nsIURI arg1, String arg2);

  public void cancelRefreshURITimers();

}
