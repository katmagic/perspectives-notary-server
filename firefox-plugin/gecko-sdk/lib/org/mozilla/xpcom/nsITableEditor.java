/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsITableEditor">
 **/

package org.mozilla.xpcom;

public interface nsITableEditor extends nsISupports
{
  public static final String NS_ITABLEEDITOR_IID =
    "{4805e684-49b9-11d3-9ce4-ed60bd6cb5bc}";

  public static final short eNoSearch = 0;

  public static final short ePreviousColumn = 1;

  public static final short ePreviousRow = 2;

  public void insertTableCell(int arg1, boolean arg2);

  public void insertTableColumn(int arg1, boolean arg2);

  public void insertTableRow(int arg1, boolean arg2);

  public void deleteTable();

  public void deleteTableCellContents();

  public void deleteTableCell(int arg1);

  public void deleteTableColumn(int arg1);

  public void deleteTableRow(int arg1);

  public void selectTableCell();

  public void selectBlockOfCells(nsIDOMElement arg1, nsIDOMElement arg2);

  public void selectTableRow();

  public void selectTableColumn();

  public void selectTable();

  public void selectAllTableCells();

  public nsIDOMElement switchTableCellHeaderType(nsIDOMElement arg1);

  public void joinTableCells(boolean arg1);

  public void splitTableCell();

  public void normalizeTable(nsIDOMElement arg1);

  public void getCellIndexes(nsIDOMElement arg1, int[] arg2, int[] arg3);

  public void getTableSize(nsIDOMElement arg1, int[] arg2, int[] arg3);

  public nsIDOMElement getCellAt(nsIDOMElement arg1, int arg2, int arg3);

  public void getCellDataAt(nsIDOMElement arg1, int arg2, int arg3, nsIDOMElement[] arg4, int[] arg5, int[] arg6, int[] arg7, int[] arg8, int[] arg9, int[] arg10, boolean[] arg11);

  public nsIDOMNode getFirstRow(nsIDOMElement arg1);

  public nsIDOMNode getNextRow(nsIDOMNode arg1);

  public void setSelectionAfterTableEdit(nsIDOMElement arg1, int arg2, int arg3, int arg4, boolean arg5);

  public nsIDOMElement getSelectedOrParentTableElement(String arg1, int[] arg2);

  public long getSelectedCellsType(nsIDOMElement arg1);

  public nsIDOMElement getFirstSelectedCell(nsIDOMRange[] arg1);

  public nsIDOMElement getFirstSelectedCellInTable(int[] arg1, int[] arg2);

  public nsIDOMElement getNextSelectedCell(nsIDOMRange[] arg1);

}
