/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsISVGPathGeometryS">
 **/

package org.mozilla.xpcom;

public interface nsISVGPathGeometrySource extends nsISVGGeometrySource
{
  public static final String NS_ISVGPATHGEOMETRYSOURCE_IID =
    "{73c9350e-6b0b-4458-aa24-aa5333476eff}";

  public static final long UPDATEMASK_PATH = 32768L;

  public static final int HITTEST_MASK_FILL = 1;

  public static final int HITTEST_MASK_STROKE = 2;

  public static final long UPDATEMASK_HITTEST_MASK = 65536L;

  public static final int SHAPE_RENDERING_AUTO = 0;

  public static final int SHAPE_RENDERING_OPTIMIZESPEED = 1;

  public static final int SHAPE_RENDERING_CRISPEDGES = 2;

  public static final int SHAPE_RENDERING_GEOMETRICPRECISION = 3;

  public void constructPath(nsISVGRendererPathBuilder arg1);

  public int getHittestMask();

  public int getShapeRendering();

}
