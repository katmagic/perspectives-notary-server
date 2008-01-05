/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIDocShellTreeNode">
 **/

package org.mozilla.xpcom;

public interface nsIDocShellTreeNode extends nsISupports
{
  public static final String NS_IDOCSHELLTREENODE_IID =
    "{37f1ab73-f224-44b1-82f0-d2834ab1cec0}";

  public int getChildCount();

  public void addChild(nsIDocShellTreeItem arg1);

  public void removeChild(nsIDocShellTreeItem arg1);

  public nsIDocShellTreeItem getChildAt(int arg1);

  public nsIDocShellTreeItem findChildWithName(String arg1, boolean arg2, boolean arg3, nsIDocShellTreeItem arg4, nsIDocShellTreeItem arg5);

}
