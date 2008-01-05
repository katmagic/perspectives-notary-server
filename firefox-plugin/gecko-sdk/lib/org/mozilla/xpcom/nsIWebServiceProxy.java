/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIWebServiceProxy">
 **/

package org.mozilla.xpcom;

public interface nsIWebServiceProxy extends nsISupports
{
  public static final String NS_IWEBSERVICEPROXY_IID =
    "{2122421c-1326-41db-87f8-25519d8a12cb}";

  public nsIWSDLPort getPort();

  public boolean getIsAsync();

  public String getQualifier();

  public nsISimpleEnumerator getPendingCalls();

  public String getPrimaryInterfaceName();

  public String getPrimaryAsyncListenerInterfaceName();

  public nsIScriptableInterfaces getInterfaces();

}
