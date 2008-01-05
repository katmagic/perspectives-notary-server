/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIHTMLInlineTableE">
 **/

package org.mozilla.xpcom;

public interface nsIHTMLInlineTableEditor extends nsISupports
{
  public static final String NS_IHTMLINLINETABLEEDITOR_IID =
    "{eda2e65c-a758-451f-9b05-77cb8de74ed2}";

  public boolean getInlineTableEditingEnabled();

  public void setInlineTableEditingEnabled(boolean arg1);

  public void showInlineTableEditingUI(nsIDOMElement arg1);

  public void hideInlineTableEditingUI();

  public void doInlineTableEditingAction(nsIDOMElement arg1);

  public void refreshInlineTableEditingUI();

}
