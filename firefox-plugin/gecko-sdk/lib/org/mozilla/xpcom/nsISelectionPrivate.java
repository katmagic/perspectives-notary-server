/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsISelectionPrivate">
 **/

package org.mozilla.xpcom;

public interface nsISelectionPrivate extends nsISupports
{
  public static final String NS_ISELECTIONPRIVATE_IID =
    "{3225ca54-d7e1-4ff5-8ee9-091b0bfcda1f}";

  public static final short ENDOFPRECEDINGLINE = 0;

  public static final short STARTOFNEXTLINE = 1;

  public static final int TABLESELECTION_NONE = 0;

  public static final int TABLESELECTION_CELL = 1;

  public static final int TABLESELECTION_ROW = 2;

  public static final int TABLESELECTION_COLUMN = 3;

  public static final int TABLESELECTION_TABLE = 4;

  public static final int TABLESELECTION_ALLCELLS = 5;

  public boolean getInterlinePosition();

  public void setInterlinePosition(boolean arg1);

  public void startBatchChanges();

  public void endBatchChanges();

  public nsIEnumerator getEnumerator();

  public String toStringWithFormat(String arg1, long arg2, int arg3);

  public void addSelectionListener(nsISelectionListener arg1);

  public void removeSelectionListener(nsISelectionListener arg1);

  public int getTableSelectionType(nsIDOMRange arg1);

}
