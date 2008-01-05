/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIDOMNSHTMLInputEl">
 **/

package org.mozilla.xpcom;

public interface nsIDOMNSHTMLInputElement extends nsISupports
{
  public static final String NS_IDOMNSHTMLINPUTELEMENT_IID =
    "{993d2efc-a768-11d3-bccd-0060b0fc76bd}";

  public nsIControllers getControllers();

  public int getTextLength();

  public int getSelectionStart();

  public void setSelectionStart(int arg1);

  public int getSelectionEnd();

  public void setSelectionEnd(int arg1);

  public void setSelectionRange(int arg1, int arg2);

}
