/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsITransactionManag">
 **/

package org.mozilla.xpcom;

public interface nsITransactionManager extends nsISupports
{
  public static final String NS_ITRANSACTIONMANAGER_IID =
    "{58e330c2-7b48-11d2-98b9-00805f297d89}";

  public void doTransaction(nsITransaction arg1);

  public void undoTransaction();

  public void redoTransaction();

  public void clear();

  public void beginBatch();

  public void endBatch();

  public int getNumberOfUndoItems();

  public int getNumberOfRedoItems();

  public int getMaxTransactionCount();

  public void setMaxTransactionCount(int arg1);

  public nsITransaction peekUndoStack();

  public nsITransaction peekRedoStack();

  public nsITransactionList getUndoList();

  public nsITransactionList getRedoList();

  public void addListener(nsITransactionListener arg1);

  public void removeListener(nsITransactionListener arg1);

}
