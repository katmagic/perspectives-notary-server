/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIDOMHTMLTableRowE">
 **/

package org.mozilla.xpcom;

public interface nsIDOMHTMLTableRowElement extends nsIDOMHTMLElement
{
  public static final String NS_IDOMHTMLTABLEROWELEMENT_IID =
    "{a6cf90b6-15b3-11d2-932e-00805f8add32}";

  public int getRowIndex();

  public int getSectionRowIndex();

  public nsIDOMHTMLCollection getCells();

  public String getAlign();

  public void setAlign(String arg1);

  public String getBgColor();

  public void setBgColor(String arg1);

  public String getCh();

  public void setCh(String arg1);

  public String getChOff();

  public void setChOff(String arg1);

  public String getVAlign();

  public void setVAlign(String arg1);

  public nsIDOMHTMLElement insertCell(int arg1);

  public void deleteCell(int arg1);

}
