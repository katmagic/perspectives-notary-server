/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIProtocolProxySer">
 **/

package org.mozilla.xpcom;

public interface nsIProtocolProxyService extends nsISupports
{
  public static final String NS_IPROTOCOLPROXYSERVICE_IID =
    "{e38ab577-786e-4a7f-936b-7ae4c7d877b2}";

  public static final long RESOLVE_NON_BLOCKING = 1L;

  public nsIProxyInfo resolve(nsIURI arg1, long arg2);

  public nsICancelable asyncResolve(nsIURI arg1, long arg2, nsIProtocolProxyCallback arg3);

  public nsIProxyInfo newProxyInfo(String arg1, String arg2, int arg3, long arg4, long arg5, nsIProxyInfo arg6);

  public nsIProxyInfo getFailoverForProxy(nsIProxyInfo arg1, nsIURI arg2, long arg3);

  public void registerFilter(nsIProtocolProxyFilter arg1, long arg2);

  public void unregisterFilter(nsIProtocolProxyFilter arg1);

}
