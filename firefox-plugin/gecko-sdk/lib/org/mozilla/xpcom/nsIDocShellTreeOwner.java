/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIDocShellTreeOwne">
 **/

package org.mozilla.xpcom;

public interface nsIDocShellTreeOwner extends nsISupports
{
  public static final String NS_IDOCSHELLTREEOWNER_IID =
    "{9e508466-5ebb-4618-abfa-9ad47bed0b2e}";

  public nsIDocShellTreeItem findItemWithName(String arg1, nsIDocShellTreeItem arg2, nsIDocShellTreeItem arg3);

  public void contentShellAdded(nsIDocShellTreeItem arg1, boolean arg2, String arg3);

  public nsIDocShellTreeItem getPrimaryContentShell();

  public void sizeShellTo(nsIDocShellTreeItem arg1, int arg2, int arg3);

  public void setPersistence(boolean arg1, boolean arg2, boolean arg3);

  public void getPersistence(boolean[] arg1, boolean[] arg2, boolean[] arg3);

}
