/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIPrefService">
 **/

package org.mozilla.xpcom;

public interface nsIPrefService extends nsISupports
{
  public static final String NS_IPREFSERVICE_IID =
    "{decb9cc7-c08f-4ea5-be91-a8fc637ce2d2}";

  public void readUserPrefs(nsIFile arg1);

  public void resetPrefs();

  public void resetUserPrefs();

  public void savePrefFile(nsIFile arg1);

  public nsIPrefBranch getBranch(String arg1);

  public nsIPrefBranch getDefaultBranch(String arg1);

}
