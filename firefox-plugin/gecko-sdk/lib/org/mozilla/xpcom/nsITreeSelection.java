/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsITreeSelection">
 **/

package org.mozilla.xpcom;

public interface nsITreeSelection extends nsISupports
{
  public static final String NS_ITREESELECTION_IID =
    "{f8a13364-184e-4da3-badf-5c04837537f8}";

  public nsITreeBoxObject getTree();

  public void setTree(nsITreeBoxObject arg1);

  public boolean getSingle();

  public int getCount();

  public boolean isSelected(int arg1);

  public void select(int arg1);

  public void timedSelect(int arg1, int arg2);

  public void toggleSelect(int arg1);

  public void rangedSelect(int arg1, int arg2, boolean arg3);

  public void clearRange(int arg1, int arg2);

  public void clearSelection();

  public void invertSelection();

  public void selectAll();

  public int getRangeCount();

  public void getRangeAt(int arg1, int[] arg2, int[] arg3);

  public void invalidateSelection();

  public void adjustSelection(int arg1, int arg2);

  public boolean getSelectEventsSuppressed();

  public void setSelectEventsSuppressed(boolean arg1);

  public int getCurrentIndex();

  public void setCurrentIndex(int arg1);

  public int getShiftSelectPivot();

}
