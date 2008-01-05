/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIDOMNSHTMLTextAre">
 **/

package org.mozilla.xpcom;

public interface nsIDOMNSHTMLTextAreaElement extends nsISupports
{
  public static final String NS_IDOMNSHTMLTEXTAREAELEMENT_IID =
    "{ca066b44-9ddf-11d3-bccc-0060b0fc76bd}";

  public nsIControllers getControllers();

  public int getTextLength();

  public int getSelectionStart();

  public void setSelectionStart(int arg1);

  public int getSelectionEnd();

  public void setSelectionEnd(int arg1);

  public void setSelectionRange(int arg1, int arg2);

}
