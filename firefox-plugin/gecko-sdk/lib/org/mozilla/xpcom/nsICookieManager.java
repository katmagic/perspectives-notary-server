/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsICookieManager">
 **/

package org.mozilla.xpcom;

public interface nsICookieManager extends nsISupports
{
  public static final String NS_ICOOKIEMANAGER_IID =
    "{aaab6710-0f2c-11d5-a53b-0010a401eb10}";

  public void removeAll();

  public nsISimpleEnumerator getEnumerator();

  public void remove(String arg1, String arg2, String arg3, boolean arg4);

}
