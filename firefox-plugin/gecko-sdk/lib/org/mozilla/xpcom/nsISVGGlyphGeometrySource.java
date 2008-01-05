/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsISVGGlyphGeometry">
 **/

package org.mozilla.xpcom;

public interface nsISVGGlyphGeometrySource extends nsISVGGlyphMetricsSource
{
  public static final String NS_ISVGGLYPHGEOMETRYSOURCE_IID =
    "{b36065f1-c52b-4eda-b9ad-e483cf1a63bf}";

  public static final long UPDATEMASK_METRICS = 262144L;

  public static final long UPDATEMASK_X = 524288L;

  public static final long UPDATEMASK_Y = 1048576L;

  public static final long UPDATEMASK_HAS_HIGHLIGHT = 2097152L;

  public static final long UPDATEMASK_HIGHLIGHT = 4194304L;

  public nsISVGRendererGlyphMetrics getMetrics();

  public float getX();

  public float getY();

  public boolean getHasHighlight();

}
