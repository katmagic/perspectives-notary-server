/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsISVGGeometrySourc">
 **/

package org.mozilla.xpcom;

public interface nsISVGGeometrySource extends nsISupports
{
  public static final String NS_ISVGGEOMETRYSOURCE_IID =
    "{b2c3119b-a27d-4b25-97a9-a9d60981a95e}";

  public static final long UPDATEMASK_NOTHING = 0L;

  public static final long UPDATEMASK_ALL = 4294967295L;

  public static final long UPDATEMASK_PRES_CONTEXT = 1L;

  public static final long UPDATEMASK_CANVAS_TM = 2L;

  public static final long UPDATEMASK_STROKE_OPACITY = 4L;

  public static final long UPDATEMASK_STROKE_WIDTH = 8L;

  public static final long UPDATEMASK_STROKE_DASH_ARRAY = 16L;

  public static final long UPDATEMASK_STROKE_DASHOFFSET = 32L;

  public static final int STROKE_LINECAP_BUTT = 0;

  public static final int STROKE_LINECAP_ROUND = 1;

  public static final int STROKE_LINECAP_SQUARE = 2;

  public static final long UPDATEMASK_STROKE_LINECAP = 64L;

  public static final int STROKE_LINEJOIN_MITER = 0;

  public static final int STROKE_LINEJOIN_ROUND = 1;

  public static final int STROKE_LINEJOIN_BEVEL = 2;

  public static final long UPDATEMASK_STROKE_LINEJOIN = 128L;

  public static final long UPDATEMASK_STROKE_MITERLIMIT = 256L;

  public static final long UPDATEMASK_FILL_OPACITY = 512L;

  public static final int FILL_RULE_NONZERO = 0;

  public static final int FILL_RULE_EVENODD = 1;

  public static final long UPDATEMASK_FILL_RULE = 1024L;

  public static final int PAINT_TYPE_NONE = 0;

  public static final int PAINT_TYPE_SOLID_COLOR = 1;

  public static final int PAINT_TYPE_SERVER = 2;

  public static final int PAINT_TYPE_GRADIENT = 3;

  public static final int PAINT_TYPE_PATTERN = 4;

  public static final long UPDATEMASK_STROKE_PAINT_TYPE = 2048L;

  public static final long UPDATEMASK_STROKE_PAINT = 4096L;

  public static final long UPDATEMASK_FILL_PAINT_TYPE = 16384L;

  public static final long UPDATEMASK_FILL_PAINT = 32768L;

  public nsISupports getPresContext();

  public nsIDOMSVGMatrix getCanvasTM();

  public float getStrokeOpacity();

  public float getStrokeWidth();

  public void getStrokeDashArray(float[][] arg1, long[] arg2);

  public float getStrokeDashoffset();

  public int getStrokeLinecap();

  public int getStrokeLinejoin();

  public float getStrokeMiterlimit();

  public float getFillOpacity();

  public int getFillRule();

  public int getClipRule();

  public int getStrokePaintType();

  public int getStrokePaintServerType();

  public long getStrokePaint();

  public void getStrokeGradient(nsISupports[] arg1);

  public int getFillPaintType();

  public int getFillPaintServerType();

  public long getFillPaint();

  public void getFillGradient(nsISupports[] arg1);

  public boolean isClipChild();

}
