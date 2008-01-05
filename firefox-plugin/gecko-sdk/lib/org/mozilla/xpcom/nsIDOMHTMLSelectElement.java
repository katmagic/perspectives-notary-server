/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIDOMHTMLSelectEle">
 **/

package org.mozilla.xpcom;

public interface nsIDOMHTMLSelectElement extends nsIDOMHTMLElement
{
  public static final String NS_IDOMHTMLSELECTELEMENT_IID =
    "{a6cf9090-15b3-11d2-932e-00805f8add32}";

  public String getType();

  public int getSelectedIndex();

  public void setSelectedIndex(int arg1);

  public String getValue();

  public void setValue(String arg1);

  public long getLength();

  public void setLength(long arg1);

  public nsIDOMHTMLFormElement getForm();

  public nsIDOMHTMLOptionsCollection getOptions();

  public boolean getDisabled();

  public void setDisabled(boolean arg1);

  public boolean getMultiple();

  public void setMultiple(boolean arg1);

  public String getName();

  public void setName(String arg1);

  public int getSize();

  public void setSize(int arg1);

  public int getTabIndex();

  public void setTabIndex(int arg1);

  public void add(nsIDOMHTMLElement arg1, nsIDOMHTMLElement arg2);

  public void remove(int arg1);

  public void blur();

  public void focus();

}
