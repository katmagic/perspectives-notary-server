/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsICookieManager2">
 **/

package org.mozilla.xpcom;

public interface nsICookieManager2 extends nsICookieManager
{
  public static final String NS_ICOOKIEMANAGER2_IID =
    "{3e73ff5f-154e-494f-b640-3c654ba2cc2b}";

  public void add(String arg1, String arg2, String arg3, String arg4, boolean arg5, boolean arg6, long arg7);

  public boolean findMatchingCookie(nsICookie2 arg1, long[] arg2);

}
