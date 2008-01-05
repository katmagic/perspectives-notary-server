/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsITreeView">
 **/

package org.mozilla.xpcom;

public interface nsITreeView extends nsISupports
{
  public static final String NS_ITREEVIEW_IID =
    "{22f034b7-a879-43ad-baee-ba6fd4d466ce}";

  public static final short DROP_BEFORE = -1;

  public static final short DROP_ON = 0;

  public static final short DROP_AFTER = 1;

  public static final short PROGRESS_NORMAL = 1;

  public static final short PROGRESS_UNDETERMINED = 2;

  public static final short PROGRESS_NONE = 3;

  public int getRowCount();

  public nsITreeSelection getSelection();

  public void setSelection(nsITreeSelection arg1);

  public void getRowProperties(int arg1, nsISupportsArray arg2);

  public void getCellProperties(int arg1, nsITreeColumn arg2, nsISupportsArray arg3);

  public void getColumnProperties(nsITreeColumn arg1, nsISupportsArray arg2);

  public boolean isContainer(int arg1);

  public boolean isContainerOpen(int arg1);

  public boolean isContainerEmpty(int arg1);

  public boolean isSeparator(int arg1);

  public boolean isSorted();

  public boolean canDrop(int arg1, int arg2);

  public void drop(int arg1, int arg2);

  public int getParentIndex(int arg1);

  public boolean hasNextSibling(int arg1, int arg2);

  public int getLevel(int arg1);

  public String getImageSrc(int arg1, nsITreeColumn arg2);

  public int getProgressMode(int arg1, nsITreeColumn arg2);

  public String getCellValue(int arg1, nsITreeColumn arg2);

  public String getCellText(int arg1, nsITreeColumn arg2);

  public void setTree(nsITreeBoxObject arg1);

  public void toggleOpenState(int arg1);

  public void cycleHeader(nsITreeColumn arg1);

  public void selectionChanged();

  public void cycleCell(int arg1, nsITreeColumn arg2);

  public boolean isEditable(int arg1, nsITreeColumn arg2);

  public void setCellValue(int arg1, nsITreeColumn arg2, String arg3);

  public void setCellText(int arg1, nsITreeColumn arg2, String arg3);

  public void performAction(String arg1);

  public void performActionOnRow(String arg1, int arg2);

  public void performActionOnCell(String arg1, int arg2, nsITreeColumn arg3);

}
