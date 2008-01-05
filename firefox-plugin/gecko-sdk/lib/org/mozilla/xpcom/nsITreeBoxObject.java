/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsITreeBoxObject">
 **/

package org.mozilla.xpcom;

public interface nsITreeBoxObject extends nsISupports
{
  public static final String NS_ITREEBOXOBJECT_IID =
    "{55f3b431-1aa8-4e23-ad3d-a9f5644bdaa6}";

  public nsITreeColumns getColumns();

  public nsITreeView getView();

  public void setView(nsITreeView arg1);

  public boolean getFocused();

  public void setFocused(boolean arg1);

  public nsIDOMElement getTreeBody();

  public int getRowHeight();

  public int getFirstVisibleRow();

  public int getLastVisibleRow();

  public int getPageLength();

  public void ensureRowIsVisible(int arg1);

  public void scrollToRow(int arg1);

  public void scrollByLines(int arg1);

  public void scrollByPages(int arg1);

  public void invalidate();

  public void invalidateColumn(nsITreeColumn arg1);

  public void invalidateRow(int arg1);

  public void invalidateCell(int arg1, nsITreeColumn arg2);

  public void invalidateRange(int arg1, int arg2);

  public int getRowAt(int arg1, int arg2);

  public void getCellAt(int arg1, int arg2, int[] arg3, nsITreeColumn[] arg4, String arg5);

  public void getCoordsForCellItem(int arg1, nsITreeColumn arg2, String arg3, int[] arg4, int[] arg5, int[] arg6, int[] arg7);

  public boolean isCellCropped(int arg1, nsITreeColumn arg2);

  public void rowCountChanged(int arg1, int arg2);

  public void beginUpdateBatch();

  public void endUpdateBatch();

  public void clearStyleAndImageCaches();

}
