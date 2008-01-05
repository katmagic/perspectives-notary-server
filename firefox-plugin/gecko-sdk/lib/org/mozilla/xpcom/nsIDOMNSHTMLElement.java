/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIDOMNSHTMLElement">
 **/

package org.mozilla.xpcom;

public interface nsIDOMNSHTMLElement extends nsISupports
{
  public static final String NS_IDOMNSHTMLELEMENT_IID =
    "{da83b2ec-8264-4410-8496-ada3acd2ae42}";

  public int getOffsetTop();

  public int getOffsetLeft();

  public int getOffsetWidth();

  public int getOffsetHeight();

  public nsIDOMElement getOffsetParent();

  public String getInnerHTML();

  public void setInnerHTML(String arg1);

  public int getScrollTop();

  public void setScrollTop(int arg1);

  public int getScrollLeft();

  public void setScrollLeft(int arg1);

  public int getScrollHeight();

  public int getScrollWidth();

  public int getClientHeight();

  public int getClientWidth();

  public int getTabIndex();

  public void setTabIndex(int arg1);

  public void blur();

  public void focus();

  public void scrollIntoView(boolean arg1);

}
