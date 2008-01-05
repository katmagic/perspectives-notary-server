/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIDOMHTMLTextAreaE">
 **/

package org.mozilla.xpcom;

public interface nsIDOMHTMLTextAreaElement extends nsIDOMHTMLElement
{
  public static final String NS_IDOMHTMLTEXTAREAELEMENT_IID =
    "{a6cf9094-15b3-11d2-932e-00805f8add32}";

  public String getDefaultValue();

  public void setDefaultValue(String arg1);

  public nsIDOMHTMLFormElement getForm();

  public String getAccessKey();

  public void setAccessKey(String arg1);

  public int getCols();

  public void setCols(int arg1);

  public boolean getDisabled();

  public void setDisabled(boolean arg1);

  public String getName();

  public void setName(String arg1);

  public boolean getReadOnly();

  public void setReadOnly(boolean arg1);

  public int getRows();

  public void setRows(int arg1);

  public int getTabIndex();

  public void setTabIndex(int arg1);

  public String getType();

  public String getValue();

  public void setValue(String arg1);

  public void blur();

  public void focus();

  public void select();

}
