/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIDragSession">
 **/

package org.mozilla.xpcom;

public interface nsIDragSession extends nsISupports
{
  public static final String NS_IDRAGSESSION_IID =
    "{cba22c53-fcce-11d2-96d4-0060b0fb9956}";

  public boolean getCanDrop();

  public void setCanDrop(boolean arg1);

  public long getDragAction();

  public void setDragAction(long arg1);

  public long getNumDropItems();

  public nsIDOMDocument getSourceDocument();

  public nsIDOMNode getSourceNode();

  public void getData(nsITransferable arg1, long arg2);

  public boolean isDataFlavorSupported(String arg1);

}
