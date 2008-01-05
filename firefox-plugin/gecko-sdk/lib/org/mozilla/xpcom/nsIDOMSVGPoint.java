/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIDOMSVGPoint">
 **/

package org.mozilla.xpcom;

public interface nsIDOMSVGPoint extends nsISupports
{
  public static final String NS_IDOMSVGPOINT_IID =
    "{45f18f8f-1315-4447-a7d5-8aeca77bdcaf}";

  public float getX();

  public void setX(float arg1);

  public float getY();

  public void setY(float arg1);

  public nsIDOMSVGPoint matrixTransform(nsIDOMSVGMatrix arg1);

}
