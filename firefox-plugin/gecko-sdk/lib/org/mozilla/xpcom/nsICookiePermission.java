/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsICookiePermission">
 **/

package org.mozilla.xpcom;

public interface nsICookiePermission extends nsISupports
{
  public static final String NS_ICOOKIEPERMISSION_IID =
    "{91f1c3ec-73a0-4bf0-bdc5-348a1f181b0e}";

  public static final int ACCESS_DEFAULT = 0;

  public static final int ACCESS_ALLOW = 1;

  public static final int ACCESS_DENY = 2;

  public static final int ACCESS_SESSION = 8;

  public void setAccess(nsIURI arg1, int arg2);

  public int canAccess(nsIURI arg1, nsIURI arg2, nsIChannel arg3);

  public boolean canSetCookie(nsIURI arg1, nsIChannel arg2, nsICookie2 arg3, boolean[] arg4, long[] arg5);

}
