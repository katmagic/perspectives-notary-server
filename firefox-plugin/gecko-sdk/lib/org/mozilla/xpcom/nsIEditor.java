/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIEditor">
 **/

package org.mozilla.xpcom;

public interface nsIEditor extends nsISupports
{
  public static final String NS_IEDITOR_IID =
    "{d4882ffb-e927-408b-96be-d4391b456fa9}";

  public static final short eNone = 0;

  public static final short eNext = 1;

  public static final short ePrevious = 2;

  public static final short eNextWord = 3;

  public static final short ePreviousWord = 4;

  public static final short eToBeginningOfLine = 5;

  public static final short eToEndOfLine = 6;

  public nsISelection getSelection();

  public void setAttributeOrEquivalent(nsIDOMElement arg1, String arg2, String arg3, boolean arg4);

  public void removeAttributeOrEquivalent(nsIDOMElement arg1, String arg2, boolean arg3);

  public void postCreate();

  public void preDestroy();

  public long getFlags();

  public void setFlags(long arg1);

  public String getContentsMIMEType();

  public void setContentsMIMEType(String arg1);

  public boolean getIsDocumentEditable();

  public nsIDOMDocument getDocument();

  public nsIDOMElement getRootElement();

  public nsISelectionController getSelectionController();

  public void deleteSelection(short arg1);

  public boolean getDocumentIsEmpty();

  public boolean getDocumentModified();

  public String getDocumentCharacterSet();

  public void setDocumentCharacterSet(String arg1);

  public void resetModificationCount();

  public int getModificationCount();

  public void incrementModificationCount(int arg1);

  public nsITransactionManager getTransactionManager();

  public void doTransaction(nsITransaction arg1);

  public void enableUndo(boolean arg1);

  public void undo(long arg1);

  public void canUndo(boolean[] arg1, boolean[] arg2);

  public void redo(long arg1);

  public void canRedo(boolean[] arg1, boolean[] arg2);

  public void beginTransaction();

  public void endTransaction();

  public void beginPlaceHolderTransaction(nsIAtom arg1);

  public void endPlaceHolderTransaction();

  public boolean shouldTxnSetSelection();

  public void setShouldTxnSetSelection(boolean arg1);

  public nsIInlineSpellChecker getInlineSpellChecker();

  public void cut();

  public boolean canCut();

  public void copy();

  public boolean canCopy();

  public void paste(int arg1);

  public boolean canPaste(int arg1);

  public void selectAll();

  public void beginningOfDocument();

  public void endOfDocument();

  public boolean canDrag(nsIDOMEvent arg1);

  public void doDrag(nsIDOMEvent arg1);

  public void insertFromDrop(nsIDOMEvent arg1);

  public void setAttribute(nsIDOMElement arg1, String arg2, String arg3);

  public boolean getAttributeValue(nsIDOMElement arg1, String arg2, String arg3);

  public void removeAttribute(nsIDOMElement arg1, String arg2);

  public void cloneAttribute(String arg1, nsIDOMNode arg2, nsIDOMNode arg3);

  public void cloneAttributes(nsIDOMNode arg1, nsIDOMNode arg2);

  public nsIDOMNode createNode(String arg1, nsIDOMNode arg2, int arg3);

  public void insertNode(nsIDOMNode arg1, nsIDOMNode arg2, int arg3);

  public void splitNode(nsIDOMNode arg1, int arg2, nsIDOMNode[] arg3);

  public void joinNodes(nsIDOMNode arg1, nsIDOMNode arg2, nsIDOMNode arg3);

  public void deleteNode(nsIDOMNode arg1);

  public void markNodeDirty(nsIDOMNode arg1);

  public void switchTextDirection();

  public String outputToString(String arg1, long arg2);

  public void outputToStream(nsIOutputStream arg1, String arg2, String arg3, long arg4);

  public void addEditorObserver(nsIEditorObserver arg1);

  public void removeEditorObserver(nsIEditorObserver arg1);

  public void addEditActionListener(nsIEditActionListener arg1);

  public void removeEditActionListener(nsIEditActionListener arg1);

  public void addDocumentStateListener(nsIDocumentStateListener arg1);

  public void removeDocumentStateListener(nsIDocumentStateListener arg1);

  public void dumpContentTree();

  public void debugDumpContent();

  public void debugUnitTests(int[] arg1, int[] arg2);

}
