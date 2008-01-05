/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIUpdateChecker">
 **/

package org.mozilla.xpcom;

public interface nsIUpdateChecker extends nsISupports
{
  public static final String NS_IUPDATECHECKER_IID =
    "{877ace25-8bc5-452a-8586-9c1cf2871994}";

  public static final int CURRENT_CHECK = 1;

  public static final int CURRENT_SESSION = 2;

  public static final int ANY_CHECKS = 3;

  public void checkForUpdates(nsIUpdateCheckListener arg1, boolean arg2);

  public void stopChecking(int arg1);

}
