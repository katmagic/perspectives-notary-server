/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIDOMSVGTransform">
 **/

package org.mozilla.xpcom;

public interface nsIDOMSVGTransform extends nsISupports
{
  public static final String NS_IDOMSVGTRANSFORM_IID =
    "{29cc2e14-6d18-4710-bda9-a88d9d3bc8dc}";

  public static final int SVG_TRANSFORM_UNKNOWN = 0;

  public static final int SVG_TRANSFORM_MATRIX = 1;

  public static final int SVG_TRANSFORM_TRANSLATE = 2;

  public static final int SVG_TRANSFORM_SCALE = 3;

  public static final int SVG_TRANSFORM_ROTATE = 4;

  public static final int SVG_TRANSFORM_SKEWX = 5;

  public static final int SVG_TRANSFORM_SKEWY = 6;

  public int getType();

  public nsIDOMSVGMatrix getMatrix();

  public float getAngle();

  public void setMatrix(nsIDOMSVGMatrix arg1);

  public void setTranslate(float arg1, float arg2);

  public void setScale(float arg1, float arg2);

  public void setRotate(float arg1, float arg2, float arg3);

  public void setSkewX(float arg1);

  public void setSkewY(float arg1);

}
