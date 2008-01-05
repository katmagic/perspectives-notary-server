/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIXmlRpcClientList">
 **/

package org.mozilla.xpcom;

public interface nsIXmlRpcClientListener extends nsISupports
{
  public static final String NS_IXMLRPCCLIENTLISTENER_IID =
    "{27e60cd8-6d63-4d87-b7d1-82c09e0c7363}";

  public void onResult(nsIXmlRpcClient arg1, nsISupports arg2, nsISupports arg3);

  public void onFault(nsIXmlRpcClient arg1, nsISupports arg2, nsIXmlRpcFault arg3);

  public void onError(nsIXmlRpcClient arg1, nsISupports arg2, long arg3, String arg4);

}
