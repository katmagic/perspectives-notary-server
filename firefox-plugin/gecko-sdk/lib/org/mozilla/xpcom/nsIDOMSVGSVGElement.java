/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIDOMSVGSVGElement">
 **/

package org.mozilla.xpcom;

public interface nsIDOMSVGSVGElement extends nsIDOMSVGElement
{
  public static final String NS_IDOMSVGSVGELEMENT_IID =
    "{67b8f41e-3577-4c8a-b1de-bef51186fe08}";

  public nsIDOMSVGAnimatedLength getX();

  public nsIDOMSVGAnimatedLength getY();

  public nsIDOMSVGAnimatedLength getWidth();

  public nsIDOMSVGAnimatedLength getHeight();

  public String getContentScriptType();

  public void setContentScriptType(String arg1);

  public String getContentStyleType();

  public void setContentStyleType(String arg1);

  public nsIDOMSVGRect getViewport();

  public float getPixelUnitToMillimeterX();

  public float getPixelUnitToMillimeterY();

  public float getScreenPixelToMillimeterX();

  public float getScreenPixelToMillimeterY();

  public boolean getUseCurrentView();

  public void setUseCurrentView(boolean arg1);

  public nsISupports getCurrentView();

  public float getCurrentScale();

  public void setCurrentScale(float arg1);

  public nsIDOMSVGPoint getCurrentTranslate();

  public long suspendRedraw(long arg1);

  public void unsuspendRedraw(long arg1);

  public void unsuspendRedrawAll();

  public void forceRedraw();

  public void pauseAnimations();

  public void unpauseAnimations();

  public boolean animationsPaused();

  public float getCurrentTime();

  public void setCurrentTime(float arg1);

  public nsIDOMNodeList getIntersectionList(nsIDOMSVGRect arg1, nsIDOMSVGElement arg2);

  public nsIDOMNodeList getEnclosureList(nsIDOMSVGRect arg1, nsIDOMSVGElement arg2);

  public boolean checkIntersection(nsIDOMSVGElement arg1, nsIDOMSVGRect arg2);

  public boolean checkEnclosure(nsIDOMSVGElement arg1, nsIDOMSVGRect arg2);

  public void deSelectAll();

  public nsIDOMSVGNumber createSVGNumber();

  public nsIDOMSVGLength createSVGLength();

  public nsIDOMSVGAngle createSVGAngle();

  public nsIDOMSVGPoint createSVGPoint();

  public nsIDOMSVGMatrix createSVGMatrix();

  public nsIDOMSVGRect createSVGRect();

  public nsIDOMSVGTransform createSVGTransform();

  public nsIDOMSVGTransform createSVGTransformFromMatrix(nsIDOMSVGMatrix arg1);

  public String createSVGString();

  public nsIDOMElement getElementById(String arg1);

  public nsIDOMSVGMatrix getViewboxToViewportTransform();

}
