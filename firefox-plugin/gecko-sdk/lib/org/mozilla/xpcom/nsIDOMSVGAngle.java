/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIDOMSVGAngle">
 **/

package org.mozilla.xpcom;

public interface nsIDOMSVGAngle extends nsISupports
{
  public static final String NS_IDOMSVGANGLE_IID =
    "{58b6190e-37b3-412a-ba02-1d5ad6c6ea7c}";

  public static final int SVG_ANGLETYPE_UNKNOWN = 0;

  public static final int SVG_ANGLETYPE_UNSPECIFIED = 1;

  public static final int SVG_ANGLETYPE_DEG = 2;

  public static final int SVG_ANGLETYPE_RAD = 3;

  public static final int SVG_ANGLETYPE_GRAD = 4;

  public int getUnitType();

  public float getValue();

  public void setValue(float arg1);

  public float getValueInSpecifiedUnits();

  public void setValueInSpecifiedUnits(float arg1);

  public String getValueAsString();

  public void setValueAsString(String arg1);

  public void newValueSpecifiedUnits(int arg1, float arg2);

  public void convertToSpecifiedUnits(int arg1);

}
