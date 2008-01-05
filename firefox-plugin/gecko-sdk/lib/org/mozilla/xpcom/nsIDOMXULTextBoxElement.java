/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIDOMXULTextBoxEle">
 **/

package org.mozilla.xpcom;

public interface nsIDOMXULTextBoxElement extends nsIDOMXULControlElement
{
  public static final String NS_IDOMXULTEXTBOXELEMENT_IID =
    "{71135b6c-294e-4634-a8e4-a72398f1e72a}";

  public nsIDOMNode getInputField();

  public int getTextLength();

  public int getMaxLength();

  public void setMaxLength(int arg1);

  public int getSize();

  public void setSize(int arg1);

  public int getSelectionStart();

  public void setSelectionStart(int arg1);

  public int getSelectionEnd();

  public void setSelectionEnd(int arg1);

  public String getValue();

  public void setValue(String arg1);

  public String getType();

  public void setType(String arg1);

  public void select();

  public void setSelectionRange(int arg1, int arg2);

}
