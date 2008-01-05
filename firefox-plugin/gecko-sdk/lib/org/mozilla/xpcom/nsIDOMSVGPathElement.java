/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIDOMSVGPathElemen">
 **/

package org.mozilla.xpcom;

public interface nsIDOMSVGPathElement extends nsIDOMSVGElement
{
  public static final String NS_IDOMSVGPATHELEMENT_IID =
    "{2b19e692-3338-440f-a998-3cb1e8474999}";

  public nsIDOMSVGAnimatedNumber getPathLength();

  public float getTotalLength();

  public nsIDOMSVGPoint getPointAtLength(float arg1);

  public long getPathSegAtLength(float arg1);

  public nsIDOMSVGPathSegClosePath createSVGPathSegClosePath();

  public nsIDOMSVGPathSegMovetoAbs createSVGPathSegMovetoAbs(float arg1, float arg2);

  public nsIDOMSVGPathSegMovetoRel createSVGPathSegMovetoRel(float arg1, float arg2);

  public nsIDOMSVGPathSegLinetoAbs createSVGPathSegLinetoAbs(float arg1, float arg2);

  public nsIDOMSVGPathSegLinetoRel createSVGPathSegLinetoRel(float arg1, float arg2);

  public nsIDOMSVGPathSegCurvetoCubicAbs createSVGPathSegCurvetoCubicAbs(float arg1, float arg2, float arg3, float arg4, float arg5, float arg6);

  public nsIDOMSVGPathSegCurvetoCubicRel createSVGPathSegCurvetoCubicRel(float arg1, float arg2, float arg3, float arg4, float arg5, float arg6);

  public nsIDOMSVGPathSegCurvetoQuadraticAbs createSVGPathSegCurvetoQuadraticAbs(float arg1, float arg2, float arg3, float arg4);

  public nsIDOMSVGPathSegCurvetoQuadraticRel createSVGPathSegCurvetoQuadraticRel(float arg1, float arg2, float arg3, float arg4);

  public nsIDOMSVGPathSegArcAbs createSVGPathSegArcAbs(float arg1, float arg2, float arg3, float arg4, float arg5, boolean arg6, boolean arg7);

  public nsIDOMSVGPathSegArcRel createSVGPathSegArcRel(float arg1, float arg2, float arg3, float arg4, float arg5, boolean arg6, boolean arg7);

  public nsIDOMSVGPathSegLinetoHorizontalAbs createSVGPathSegLinetoHorizontalAbs(float arg1);

  public nsIDOMSVGPathSegLinetoHorizontalRel createSVGPathSegLinetoHorizontalRel(float arg1);

  public nsIDOMSVGPathSegLinetoVerticalAbs createSVGPathSegLinetoVerticalAbs(float arg1);

  public nsIDOMSVGPathSegLinetoVerticalRel createSVGPathSegLinetoVerticalRel(float arg1);

  public nsIDOMSVGPathSegCurvetoCubicSmoothAbs createSVGPathSegCurvetoCubicSmoothAbs(float arg1, float arg2, float arg3, float arg4);

  public nsIDOMSVGPathSegCurvetoCubicSmoothRel createSVGPathSegCurvetoCubicSmoothRel(float arg1, float arg2, float arg3, float arg4);

  public nsIDOMSVGPathSegCurvetoQuadraticSmoothAbs createSVGPathSegCurvetoQuadraticSmoothAbs(float arg1, float arg2);

  public nsIDOMSVGPathSegCurvetoQuadraticSmoothRel createSVGPathSegCurvetoQuadraticSmoothRel(float arg1, float arg2);

}
