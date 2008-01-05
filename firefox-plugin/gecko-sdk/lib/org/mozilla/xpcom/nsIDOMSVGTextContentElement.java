/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIDOMSVGTextConten">
 **/

package org.mozilla.xpcom;

public interface nsIDOMSVGTextContentElement extends nsIDOMSVGElement
{
  public static final String NS_IDOMSVGTEXTCONTENTELEMENT_IID =
    "{87ad94bc-07c9-412b-b2d8-de245a2e84a5}";

  public static final int LENGTHADJUST_UNKNOWN = 0;

  public static final int LENGTHADJUST_SPACING = 1;

  public static final int LENGTHADJUST_SPACINGANDGLYPHS = 2;

  public nsIDOMSVGAnimatedLength getTextLength();

  public nsIDOMSVGAnimatedEnumeration getLengthAdjust();

  public int getNumberOfChars();

  public float getComputedTextLength();

  public float getSubStringLength(long arg1, long arg2);

  public nsIDOMSVGPoint getStartPositionOfChar(long arg1);

  public nsIDOMSVGPoint getEndPositionOfChar(long arg1);

  public nsIDOMSVGRect getExtentOfChar(long arg1);

  public float getRotationOfChar(long arg1);

  public int getCharNumAtPosition(nsIDOMSVGPoint arg1);

  public void selectSubString(long arg1, long arg2);

}
