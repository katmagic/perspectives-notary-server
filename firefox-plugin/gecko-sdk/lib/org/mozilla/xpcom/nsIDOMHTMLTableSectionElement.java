/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIDOMHTMLTableSect">
 **/

package org.mozilla.xpcom;

public interface nsIDOMHTMLTableSectionElement extends nsIDOMHTMLElement
{
  public static final String NS_IDOMHTMLTABLESECTIONELEMENT_IID =
    "{a6cf90b5-15b3-11d2-932e-00805f8add32}";

  public String getAlign();

  public void setAlign(String arg1);

  public String getCh();

  public void setCh(String arg1);

  public String getChOff();

  public void setChOff(String arg1);

  public String getVAlign();

  public void setVAlign(String arg1);

  public nsIDOMHTMLCollection getRows();

  public nsIDOMHTMLElement insertRow(int arg1);

  public void deleteRow(int arg1);

}
