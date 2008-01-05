/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIBoxObject">
 **/

package org.mozilla.xpcom;

public interface nsIBoxObject extends nsISupports
{
  public static final String NS_IBOXOBJECT_IID =
    "{caabf76f-9d35-401f-beac-3955817c645c}";

  public nsIDOMElement getElement();

  public nsIBoxLayoutManager getLayoutManager();

  public void setLayoutManager(nsIBoxLayoutManager arg1);

  public nsIBoxPaintManager getPaintManager();

  public void setPaintManager(nsIBoxPaintManager arg1);

  public int getX();

  public int getY();

  public int getScreenX();

  public int getScreenY();

  public int getWidth();

  public int getHeight();

  public nsISupports getPropertyAsSupports(String arg1);

  public void setPropertyAsSupports(String arg1, nsISupports arg2);

  public String getProperty(String arg1);

  public void setProperty(String arg1, String arg2);

  public void removeProperty(String arg1);

  public nsIDOMElement getParentBox();

  public nsIDOMElement getFirstChild();

  public nsIDOMElement getLastChild();

  public nsIDOMElement getNextSibling();

  public nsIDOMElement getPreviousSibling();

  public String getLookAndFeelMetric(String arg1);

}
