/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIURIContentListen">
 **/

package org.mozilla.xpcom;

public interface nsIURIContentListener extends nsISupports
{
  public static final String NS_IURICONTENTLISTENER_IID =
    "{94928ab3-8b63-11d3-989d-001083010e9b}";

  public boolean onStartURIOpen(nsIURI arg1);

  public boolean doContent(String arg1, boolean arg2, nsIRequest arg3, nsIStreamListener[] arg4);

  public boolean isPreferred(String arg1, String[] arg2);

  public boolean canHandleContent(String arg1, boolean arg2, String[] arg3);

  public nsISupports getLoadCookie();

  public void setLoadCookie(nsISupports arg1);

  public nsIURIContentListener getParentContentListener();

  public void setParentContentListener(nsIURIContentListener arg1);

}
