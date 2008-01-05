/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIWebServiceProxyF">
 **/

package org.mozilla.xpcom;

public interface nsIWebServiceProxyFactory extends nsISupports
{
  public static final String NS_IWEBSERVICEPROXYFACTORY_IID =
    "{693611be-bb38-40e0-a98e-b46ff8a5bcca}";

  public nsIWebServiceProxy createProxy(String arg1, String arg2, String arg3, boolean arg4);

  public void createProxyAsync(String arg1, String arg2, String arg3, boolean arg4, nsIWebServiceProxyCreationListener arg5);

}
