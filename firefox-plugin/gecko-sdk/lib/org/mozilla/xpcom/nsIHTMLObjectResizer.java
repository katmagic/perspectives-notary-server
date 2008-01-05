/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIHTMLObjectResize">
 **/

package org.mozilla.xpcom;

public interface nsIHTMLObjectResizer extends nsISupports
{
  public static final String NS_IHTMLOBJECTRESIZER_IID =
    "{b0338f6c-ded3-4c39-a953-56e8bae494f5}";

  public static final short eTopLeft = 0;

  public static final short eTop = 1;

  public static final short eTopRight = 2;

  public static final short eLeft = 3;

  public static final short eRight = 4;

  public static final short eBottomLeft = 5;

  public static final short eBottom = 6;

  public static final short eBottomRight = 7;

  public nsIDOMElement getResizedObject();

  public boolean getObjectResizingEnabled();

  public void setObjectResizingEnabled(boolean arg1);

  public void showResizers(nsIDOMElement arg1);

  public void hideResizers();

  public void refreshResizers();

  public void mouseDown(int arg1, int arg2, nsIDOMElement arg3);

  public void mouseUp(int arg1, int arg2, nsIDOMElement arg3);

  public void mouseMove(nsIDOMEvent arg1);

  public void addObjectResizeEventListener(nsIHTMLObjectResizeListener arg1);

  public void removeObjectResizeEventListener(nsIHTMLObjectResizeListener arg1);

}
