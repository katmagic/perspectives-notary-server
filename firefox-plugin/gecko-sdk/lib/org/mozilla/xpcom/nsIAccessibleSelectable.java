/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIAccessibleSelect">
 **/

package org.mozilla.xpcom;

public interface nsIAccessibleSelectable extends nsISupports
{
  public static final String NS_IACCESSIBLESELECTABLE_IID =
    "{34d268d6-1dd2-11b2-9d63-83a5e0ada290}";

  public nsIArray getSelectedChildren();

  public int getSelectionCount();

  public void addChildToSelection(int arg1);

  public void removeChildFromSelection(int arg1);

  public void clearSelection();

  public nsIAccessible refSelection(int arg1);

  public boolean isChildSelected(int arg1);

  public boolean selectAllSelection();

}
