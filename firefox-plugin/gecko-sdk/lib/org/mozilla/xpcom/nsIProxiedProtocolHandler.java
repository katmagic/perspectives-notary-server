/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIProxiedProtocolH">
 **/

package org.mozilla.xpcom;

public interface nsIProxiedProtocolHandler extends nsIProtocolHandler
{
  public static final String NS_IPROXIEDPROTOCOLHANDLER_IID =
    "{0a24fed4-1dd2-11b2-a75c-9f8b9a8f9ba7}";

  public nsIChannel newProxiedChannel(nsIURI arg1, nsIProxyInfo arg2);

}
