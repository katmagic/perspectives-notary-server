/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIDOMHTMLOptionEle">
 **/

package org.mozilla.xpcom;

public interface nsIDOMHTMLOptionElement extends nsIDOMHTMLElement
{
  public static final String NS_IDOMHTMLOPTIONELEMENT_IID =
    "{a6cf9092-15b3-11d2-932e-00805f8add32}";

  public nsIDOMHTMLFormElement getForm();

  public boolean getDefaultSelected();

  public void setDefaultSelected(boolean arg1);

  public String getText();

  public int getIndex();

  public boolean getDisabled();

  public void setDisabled(boolean arg1);

  public String getLabel();

  public void setLabel(String arg1);

  public boolean getSelected();

  public void setSelected(boolean arg1);

  public String getValue();

  public void setValue(String arg1);

}
