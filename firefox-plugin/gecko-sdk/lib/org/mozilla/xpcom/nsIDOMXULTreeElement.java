/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIDOMXULTreeElemen">
 **/

package org.mozilla.xpcom;

public interface nsIDOMXULTreeElement extends nsIDOMXULElement
{
  public static final String NS_IDOMXULTREEELEMENT_IID =
    "{1f8111b2-d44d-4d11-845a-a70ae06b7d04}";

  public nsITreeColumns getColumns();

  public nsITreeView getView();

  public void setView(nsITreeView arg1);

  public nsIDOMElement getBody();

  public boolean getEditable();

  public void setEditable(boolean arg1);

  public nsIDOMXULTextBoxElement getInputField();

}
