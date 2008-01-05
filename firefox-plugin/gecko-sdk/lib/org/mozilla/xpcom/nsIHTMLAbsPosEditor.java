/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIHTMLAbsPosEditor">
 **/

package org.mozilla.xpcom;

public interface nsIHTMLAbsPosEditor extends nsISupports
{
  public static final String NS_IHTMLABSPOSEDITOR_IID =
    "{91375f52-20e6-4757-9835-eb04fabe5498}";

  public boolean getSelectionContainerAbsolutelyPositioned();

  public nsIDOMElement getPositionedElement();

  public boolean getAbsolutePositioningEnabled();

  public void setAbsolutePositioningEnabled(boolean arg1);

  public boolean getSnapToGridEnabled();

  public void setSnapToGridEnabled(boolean arg1);

  public long getGridSize();

  public void setGridSize(long arg1);

  public nsIDOMElement getAbsolutelyPositionedSelectionContainer();

  public void absolutePositionSelection(boolean arg1);

  public void relativeChangeZIndex(int arg1);

  public void absolutelyPositionElement(nsIDOMElement arg1, boolean arg2);

  public void setElementPosition(nsIDOMElement arg1, int arg2, int arg3);

  public int getElementZIndex(nsIDOMElement arg1);

  public void setElementZIndex(nsIDOMElement arg1, int arg2);

  public int relativeChangeElementZIndex(nsIDOMElement arg1, int arg2);

  public void showGrabberOnElement(nsIDOMElement arg1);

  public void hideGrabber();

  public void refreshGrabber();

}
