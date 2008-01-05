/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIIOService">
 **/

package org.mozilla.xpcom;

public interface nsIIOService extends nsISupports
{
  public static final String NS_IIOSERVICE_IID =
    "{bddeda3f-9020-4d12-8c70-984ee9f7935e}";

  public nsIProtocolHandler getProtocolHandler(String arg1);

  public long getProtocolFlags(String arg1);

  public nsIURI newURI(String arg1, String arg2, nsIURI arg3);

  public nsIURI newFileURI(nsIFile arg1);

  public nsIChannel newChannelFromURI(nsIURI arg1);

  public nsIChannel newChannel(String arg1, String arg2, nsIURI arg3);

  public boolean getOffline();

  public void setOffline(boolean arg1);

  public boolean allowPort(int arg1, String arg2);

  public String extractScheme(String arg1);

}
