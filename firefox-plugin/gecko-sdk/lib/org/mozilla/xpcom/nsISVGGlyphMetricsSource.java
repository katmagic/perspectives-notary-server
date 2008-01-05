/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsISVGGlyphMetricsS">
 **/

package org.mozilla.xpcom;

public interface nsISVGGlyphMetricsSource extends nsISVGGeometrySource
{
  public static final String NS_ISVGGLYPHMETRICSSOURCE_IID =
    "{8e96a973-c8bb-43a2-8584-4976e75ca478}";

  public static final long UPDATEMASK_FONT = 32768L;

  public static final long UPDATEMASK_CHARACTER_DATA = 65536L;

  public static final int TEXT_RENDERING_AUTO = 0;

  public static final int TEXT_RENDERING_OPTIMIZESPEED = 1;

  public static final int TEXT_RENDERING_OPTIMIZELEGIBILITY = 2;

  public static final int TEXT_RENDERING_GEOMETRICPRECISION = 3;

  public static final long UPDATEMASK_TEXT_RENDERING = 131072L;

  public String getCharacterData();

  public int getTextRendering();

}
