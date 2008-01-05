/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIDOMSVGLocatable">
 **/

package org.mozilla.xpcom;

public interface nsIDOMSVGLocatable extends nsISupports
{
  public static final String NS_IDOMSVGLOCATABLE_IID =
    "{9cf4fc9c-90b2-4d66-88f5-35049b558aee}";

  public nsIDOMSVGElement getNearestViewportElement();

  public nsIDOMSVGElement getFarthestViewportElement();

  public nsIDOMSVGRect getBBox();

  public nsIDOMSVGMatrix getCTM();

  public nsIDOMSVGMatrix getScreenCTM();

  public nsIDOMSVGMatrix getTransformToElement(nsIDOMSVGElement arg1);

}
