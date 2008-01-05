/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIScreenManager">
 **/

package org.mozilla.xpcom;

public interface nsIScreenManager extends nsISupports
{
  public static final String NS_ISCREENMANAGER_IID =
    "{662e7b78-1dd2-11b2-a3d3-fc1e5f5fb9d4}";

  public nsIScreen screenForRect(int arg1, int arg2, int arg3, int arg4);

  public nsIScreen getPrimaryScreen();

  public long getNumberOfScreens();

}
