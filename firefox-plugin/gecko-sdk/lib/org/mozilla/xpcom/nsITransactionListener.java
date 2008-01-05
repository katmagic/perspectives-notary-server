/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsITransactionListe">
 **/

package org.mozilla.xpcom;

public interface nsITransactionListener extends nsISupports
{
  public static final String NS_ITRANSACTIONLISTENER_IID =
    "{58e330c4-7b48-11d2-98b9-00805f297d89}";

  public boolean willDo(nsITransactionManager arg1, nsITransaction arg2);

  public void didDo(nsITransactionManager arg1, nsITransaction arg2, long arg3);

  public boolean willUndo(nsITransactionManager arg1, nsITransaction arg2);

  public void didUndo(nsITransactionManager arg1, nsITransaction arg2, long arg3);

  public boolean willRedo(nsITransactionManager arg1, nsITransaction arg2);

  public void didRedo(nsITransactionManager arg1, nsITransaction arg2, long arg3);

  public boolean willBeginBatch(nsITransactionManager arg1);

  public void didBeginBatch(nsITransactionManager arg1, long arg2);

  public boolean willEndBatch(nsITransactionManager arg1);

  public void didEndBatch(nsITransactionManager arg1, long arg2);

  public boolean willMerge(nsITransactionManager arg1, nsITransaction arg2, nsITransaction arg3);

  public void didMerge(nsITransactionManager arg1, nsITransaction arg2, nsITransaction arg3, boolean arg4, long arg5);

}
