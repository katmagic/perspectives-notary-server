/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsISVGRendererGlyph">
 **/

package org.mozilla.xpcom;

public interface nsISVGRendererGlyphMetrics extends nsISupports
{
  public static final String NS_ISVGRENDERERGLYPHMETRICS_IID =
    "{8665f6e9-6ed6-4ff8-b511-46c8068b3960}";

  public static final int BASELINE_ALPHABETIC = 0;

  public static final int BASELINE_HANGING = 1;

  public static final int BASELINE_IDEOGRAPHC = 2;

  public static final int BASELINE_MATHEMATICAL = 3;

  public static final int BASELINE_CENTRAL = 4;

  public static final int BASELINE_MIDDLE = 5;

  public static final int BASELINE_TEXT_BEFORE_EDGE = 6;

  public static final int BASELINE_TEXT_AFTER_EDGE = 7;

  public float getAdvance();

  public nsIDOMSVGRect getBoundingBox();

  public nsIDOMSVGRect getExtentOfChar(long arg1);

  public float getBaselineOffset(int arg1);

  public boolean update(long arg1);

}
