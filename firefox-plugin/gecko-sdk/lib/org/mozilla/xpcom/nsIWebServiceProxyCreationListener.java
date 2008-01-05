/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIWebServiceProxyC">
 **/

package org.mozilla.xpcom;

public interface nsIWebServiceProxyCreationListener extends nsISupports
{
  public static final String NS_IWEBSERVICEPROXYCREATIONLISTENER_IID =
    "{a711250b-47da-4f16-a1fd-593de16375a1}";

  public void onLoad(nsIWebServiceProxy arg1);

  public void onError(nsIException arg1);

}
