/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsISSLSocketControl">
 **/

package org.mozilla.xpcom;

public interface nsISSLSocketControl extends nsISupports
{
  public static final String NS_ISSLSOCKETCONTROL_IID =
    "{8b3e8488-1dd2-11b2-b547-956290be347c}";

  public nsIInterfaceRequestor getNotificationCallbacks();

  public void setNotificationCallbacks(nsIInterfaceRequestor arg1);

  public boolean getForceHandshake();

  public void setForceHandshake(boolean arg1);

  public void proxyStartSSL();

  public void startTLS();

}
