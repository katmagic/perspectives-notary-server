/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIProtocolProxyCal">
 **/

package org.mozilla.xpcom;

public interface nsIProtocolProxyCallback extends nsISupports
{
  public static final String NS_IPROTOCOLPROXYCALLBACK_IID =
    "{a9967200-f95e-45c2-beb3-9b060d874bfd}";

  public void onProxyAvailable(nsICancelable arg1, nsIURI arg2, nsIProxyInfo arg3, long arg4);

}
