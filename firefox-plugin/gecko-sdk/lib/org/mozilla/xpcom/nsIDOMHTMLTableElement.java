/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIDOMHTMLTableElem">
 **/

package org.mozilla.xpcom;

public interface nsIDOMHTMLTableElement extends nsIDOMHTMLElement
{
  public static final String NS_IDOMHTMLTABLEELEMENT_IID =
    "{a6cf90b2-15b3-11d2-932e-00805f8add32}";

  public nsIDOMHTMLTableCaptionElement getCaption();

  public void setCaption(nsIDOMHTMLTableCaptionElement arg1);

  public nsIDOMHTMLTableSectionElement getTHead();

  public void setTHead(nsIDOMHTMLTableSectionElement arg1);

  public nsIDOMHTMLTableSectionElement getTFoot();

  public void setTFoot(nsIDOMHTMLTableSectionElement arg1);

  public nsIDOMHTMLCollection getRows();

  public nsIDOMHTMLCollection getTBodies();

  public String getAlign();

  public void setAlign(String arg1);

  public String getBgColor();

  public void setBgColor(String arg1);

  public String getBorder();

  public void setBorder(String arg1);

  public String getCellPadding();

  public void setCellPadding(String arg1);

  public String getCellSpacing();

  public void setCellSpacing(String arg1);

  public String getFrame();

  public void setFrame(String arg1);

  public String getRules();

  public void setRules(String arg1);

  public String getSummary();

  public void setSummary(String arg1);

  public String getWidth();

  public void setWidth(String arg1);

  public nsIDOMHTMLElement createTHead();

  public void deleteTHead();

  public nsIDOMHTMLElement createTFoot();

  public void deleteTFoot();

  public nsIDOMHTMLElement createCaption();

  public void deleteCaption();

  public nsIDOMHTMLElement insertRow(int arg1);

  public void deleteRow(int arg1);

}
