/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIServerSocketList">
 **/

package org.mozilla.xpcom;

public interface nsIServerSocketListener extends nsISupports
{
  public static final String NS_ISERVERSOCKETLISTENER_IID =
    "{836d98ec-fee2-4bde-b609-abd5e966eabd}";

  public void onSocketAccepted(nsIServerSocket arg1, nsISocketTransport arg2);

  public void onStopListening(nsIServerSocket arg1, long arg2);

}
