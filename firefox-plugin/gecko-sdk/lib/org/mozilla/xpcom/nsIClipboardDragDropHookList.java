/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIClipboardDragDro">
 **/

package org.mozilla.xpcom;

public interface nsIClipboardDragDropHookList extends nsISupports
{
  public static final String NS_ICLIPBOARDDRAGDROPHOOKLIST_IID =
    "{876a2015-6b66-11d7-8f18-0003938a9d96}";

  public void addClipboardDragDropHooks(nsIClipboardDragDropHooks arg1);

  public void removeClipboardDragDropHooks(nsIClipboardDragDropHooks arg1);

  public nsISimpleEnumerator getHookEnumerator();

}
