/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsICookieService">
 **/

package org.mozilla.xpcom;

public interface nsICookieService extends nsISupports
{
  public static final String NS_ICOOKIESERVICE_IID =
    "{011c3190-1434-11d6-a618-0010a401eb10}";

  public String getCookieString(nsIURI arg1, nsIChannel arg2);

  public String getCookieStringFromHttp(nsIURI arg1, nsIURI arg2, nsIChannel arg3);

  public void setCookieString(nsIURI arg1, nsIPrompt arg2, String arg3, nsIChannel arg4);

  public void setCookieStringFromHttp(nsIURI arg1, nsIURI arg2, nsIPrompt arg3, String arg4, String arg5, nsIChannel arg6);

  public boolean getCookieIconIsVisible();

}
