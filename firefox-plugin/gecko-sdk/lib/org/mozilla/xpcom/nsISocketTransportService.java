/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsISocketTransportS">
 **/

package org.mozilla.xpcom;

public interface nsISocketTransportService extends nsISupports
{
  public static final String NS_ISOCKETTRANSPORTSERVICE_IID =
    "{7b19ac06-a5fb-11d9-9f82-0011246ecd24}";

  public nsISocketTransport createTransport(String[] arg1, long arg2, String arg3, int arg4, nsIProxyInfo arg5);

}
