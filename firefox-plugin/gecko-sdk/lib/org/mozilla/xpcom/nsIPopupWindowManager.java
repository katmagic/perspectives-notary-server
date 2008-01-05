/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIPopupWindowManag">
 **/

package org.mozilla.xpcom;

public interface nsIPopupWindowManager extends nsISupports
{
  public static final String NS_IPOPUPWINDOWMANAGER_IID =
    "{3210a6aa-b464-4f57-9335-b22815567cf1}";

  public static final long ALLOW_POPUP = 1L;

  public static final long DENY_POPUP = 2L;

  public static final long ALLOW_POPUP_WITH_PREJUDICE = 3L;

  public long testPermission(nsIURI arg1);

}
