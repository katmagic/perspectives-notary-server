/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsICookieConsent">
 **/

package org.mozilla.xpcom;

public interface nsICookieConsent extends nsISupports
{
  public static final String NS_ICOOKIECONSENT_IID =
    "{f5a34f50-1f39-11d6-a627-0010a401eb10}";

  public int getConsent(nsIURI arg1, nsIHttpChannel arg2, boolean arg3, int[] arg4);

}
