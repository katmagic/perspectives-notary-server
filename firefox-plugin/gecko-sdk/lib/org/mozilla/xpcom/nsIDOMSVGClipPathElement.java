/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIDOMSVGClipPathEl">
 **/

package org.mozilla.xpcom;

public interface nsIDOMSVGClipPathElement extends nsIDOMSVGElement
{
  public static final String NS_IDOMSVGCLIPPATHELEMENT_IID =
    "{0c3f45a4-e6d0-44e7-a2f8-d128ecf1db9b}";

  public static final int SVG_CPUNITS_UNKNOWN = 0;

  public static final int SVG_CPUNITS_OBJECTBOUNDINGBOX = 1;

  public static final int SVG_CPUNITS_USERSPACEONUSE = 2;

  public nsIDOMSVGAnimatedEnumeration getClipPathUnits();

}
