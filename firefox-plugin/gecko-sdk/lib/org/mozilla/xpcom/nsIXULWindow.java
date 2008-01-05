/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIXULWindow">
 **/

package org.mozilla.xpcom;

public interface nsIXULWindow extends nsISupports
{
  public static final String NS_IXULWINDOW_IID =
    "{b6c2f9e1-53a0-45f2-a2b8-fe37861fe8a8}";

  public static final long lowestZ = 0L;

  public static final long loweredZ = 4L;

  public static final long normalZ = 5L;

  public static final long raisedZ = 6L;

  public static final long highestZ = 9L;

  public nsIDocShell getDocShell();

  public boolean getIntrinsicallySized();

  public void setIntrinsicallySized(boolean arg1);

  public nsIDocShellTreeItem getPrimaryContentShell();

  public nsIDocShellTreeItem getContentShellById(String arg1);

  public void addChildWindow(nsIXULWindow arg1);

  public void removeChildWindow(nsIXULWindow arg1);

  public void center(nsIXULWindow arg1, boolean arg2, boolean arg3);

  public void showModal();

  public long getZLevel();

  public void setZLevel(long arg1);

  public long getContextFlags();

  public void setContextFlags(long arg1);

  public long getChromeFlags();

  public void setChromeFlags(long arg1);

  public nsIXULWindow createNewWindow(int arg1, nsISupports arg2);

  public nsIXULBrowserWindow getXULBrowserWindow();

  public void setXULBrowserWindow(nsIXULBrowserWindow arg1);

}
