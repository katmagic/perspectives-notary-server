/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIDocShellTreeItem">
 **/

package org.mozilla.xpcom;

public interface nsIDocShellTreeItem extends nsISupports
{
  public static final String NS_IDOCSHELLTREEITEM_IID =
    "{7d935d63-6d2a-4600-afb5-9a4f7d68b825}";

  public static final int typeChrome = 0;

  public static final int typeContent = 1;

  public static final int typeContentWrapper = 2;

  public static final int typeChromeWrapper = 3;

  public static final int typeAll = 2147483647;

  public String getName();

  public void setName(String arg1);

  public boolean nameEquals(String arg1);

  public int getItemType();

  public void setItemType(int arg1);

  public nsIDocShellTreeItem getParent();

  public nsIDocShellTreeItem getSameTypeParent();

  public nsIDocShellTreeItem getRootTreeItem();

  public nsIDocShellTreeItem getSameTypeRootTreeItem();

  public nsIDocShellTreeItem findItemWithName(String arg1, nsISupports arg2, nsIDocShellTreeItem arg3);

  public nsIDocShellTreeOwner getTreeOwner();

  public int getChildOffset();

  public void setChildOffset(int arg1);

}
