/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIAccessibleTable">
 **/

package org.mozilla.xpcom;

public interface nsIAccessibleTable extends nsISupports
{
  public static final String NS_IACCESSIBLETABLE_IID =
    "{0a7e98a9-ca7d-42f0-bfe1-2cfc35256038}";

  public nsIAccessible getCaption();

  public void setCaption(nsIAccessible arg1);

  public String getSummary();

  public void setSummary(String arg1);

  public int getColumns();

  public nsIAccessibleTable getColumnHeader();

  public int getRows();

  public nsIAccessibleTable getRowHeader();

  public int[] getSelectedColumns(long[] arg1);

  public int[] getSelectedRows(long[] arg1);

  public nsIAccessible cellRefAt(int arg1, int arg2);

  public int getIndexAt(int arg1, int arg2);

  public int getColumnAtIndex(int arg1);

  public int getRowAtIndex(int arg1);

  public int getColumnExtentAt(int arg1, int arg2);

  public int getRowExtentAt(int arg1, int arg2);

  public String getColumnDescription(int arg1);

  public String getRowDescription(int arg1);

  public boolean isColumnSelected(int arg1);

  public boolean isRowSelected(int arg1);

  public boolean isCellSelected(int arg1, int arg2);

}
