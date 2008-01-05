/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIDOMSVGMatrix">
 **/

package org.mozilla.xpcom;

public interface nsIDOMSVGMatrix extends nsISupports
{
  public static final String NS_IDOMSVGMATRIX_IID =
    "{ec2da3ef-5a99-49ed-aaef-b5af916c14ac}";

  public float getA();

  public void setA(float arg1);

  public float getB();

  public void setB(float arg1);

  public float getC();

  public void setC(float arg1);

  public float getD();

  public void setD(float arg1);

  public float getE();

  public void setE(float arg1);

  public float getF();

  public void setF(float arg1);

  public nsIDOMSVGMatrix multiply(nsIDOMSVGMatrix arg1);

  public nsIDOMSVGMatrix inverse();

  public nsIDOMSVGMatrix translate(float arg1, float arg2);

  public nsIDOMSVGMatrix scale(float arg1);

  public nsIDOMSVGMatrix scaleNonUniform(float arg1, float arg2);

  public nsIDOMSVGMatrix rotate(float arg1);

  public nsIDOMSVGMatrix rotateFromVector(float arg1, float arg2);

  public nsIDOMSVGMatrix flipX();

  public nsIDOMSVGMatrix flipY();

  public nsIDOMSVGMatrix skewX(float arg1);

  public nsIDOMSVGMatrix skewY(float arg1);

}
