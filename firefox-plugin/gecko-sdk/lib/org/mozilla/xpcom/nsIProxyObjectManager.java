/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIProxyObjectManag">
 **/

package org.mozilla.xpcom;

public interface nsIProxyObjectManager extends nsISupports
{
  public static final String NS_IPROXYOBJECTMANAGER_IID =
    "{eea90d43-b059-11d2-915e-c12b696c9333}";

  public static final int INVOKE_SYNC = 1;

  public static final int INVOKE_ASYNC = 2;

  public static final int FORCE_PROXY_CREATION = 4;

  public nsISupports getProxyForObject(nsIEventQueue arg1, String arg2, nsISupports arg3, int arg4);

  public nsISupports getProxy(nsIEventQueue arg1, String arg2, nsISupports arg3, String arg4, int arg5);

}
