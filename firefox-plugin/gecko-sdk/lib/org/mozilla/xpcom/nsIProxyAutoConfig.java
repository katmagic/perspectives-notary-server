/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIProxyAutoConfig">
 **/

package org.mozilla.xpcom;

public interface nsIProxyAutoConfig extends nsISupports
{
  public static final String NS_IPROXYAUTOCONFIG_IID =
    "{a42619df-0a1c-46fb-8154-0e9b8f8f1ea8}";

  public void init(String arg1, String arg2);

  public String getProxyForURI(String arg1, String arg2);

}
