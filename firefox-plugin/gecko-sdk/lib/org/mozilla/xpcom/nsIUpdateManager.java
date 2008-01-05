/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIUpdateManager">
 **/

package org.mozilla.xpcom;

public interface nsIUpdateManager extends nsISupports
{
  public static final String NS_IUPDATEMANAGER_IID =
    "{fede66a9-9f96-4507-a22a-775ee885577e}";

  public nsIUpdate getUpdateAt(int arg1);

  public int getUpdateCount();

  public nsIUpdate getActiveUpdate();

  public void setActiveUpdate(nsIUpdate arg1);

  public void saveUpdates();

}
