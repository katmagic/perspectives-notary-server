/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIClipboardDragDro">
 **/

package org.mozilla.xpcom;

public interface nsIClipboardDragDropHooks extends nsISupports
{
  public static final String NS_ICLIPBOARDDRAGDROPHOOKS_IID =
    "{e03e6c5e-0d84-4c0b-8739-e6b8d51922de}";

  public boolean allowStartDrag(nsIDOMEvent arg1);

  public boolean allowDrop(nsIDOMEvent arg1, nsIDragSession arg2);

  public boolean onCopyOrDrag(nsIDOMEvent arg1, nsITransferable arg2);

  public boolean onPasteOrDrop(nsIDOMEvent arg1, nsITransferable arg2);

}
