/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIDOMSVGMarkerElem">
 **/

package org.mozilla.xpcom;

public interface nsIDOMSVGMarkerElement extends nsIDOMSVGElement
{
  public static final String NS_IDOMSVGMARKERELEMENT_IID =
    "{7d89ceb8-f985-4095-8f24-421910704e5e}";

  public static final int SVG_MARKERUNITS_UNKNOWN = 0;

  public static final int SVG_MARKERUNITS_USERSPACEONUSE = 1;

  public static final int SVG_MARKERUNITS_STROKEWIDTH = 2;

  public static final int SVG_MARKER_ORIENT_UNKNOWN = 0;

  public static final int SVG_MARKER_ORIENT_AUTO = 1;

  public static final int SVG_MARKER_ORIENT_ANGLE = 2;

  public nsIDOMSVGAnimatedLength getRefX();

  public nsIDOMSVGAnimatedLength getRefY();

  public nsIDOMSVGAnimatedEnumeration getMarkerUnits();

  public nsIDOMSVGAnimatedLength getMarkerWidth();

  public nsIDOMSVGAnimatedLength getMarkerHeight();

  public nsIDOMSVGAnimatedEnumeration getOrientType();

  public nsIDOMSVGAnimatedAngle getOrientAngle();

  public void setOrientToAuto();

  public void setOrientToAngle(nsIDOMSVGAngle arg1);

}
