/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsISVGRenderer">
 **/

package org.mozilla.xpcom;

public interface nsISVGRenderer extends nsISupports
{
  public static final String NS_ISVGRENDERER_IID =
    "{14e914e0-f283-4fd0-9d71-d3e842927007}";

  public nsISVGRendererPathGeometry createPathGeometry(nsISVGPathGeometrySource arg1);

  public nsISVGRendererGlyphMetrics createGlyphMetrics(nsISVGGlyphMetricsSource arg1);

  public nsISVGRendererGlyphGeometry createGlyphGeometry(nsISVGGlyphGeometrySource arg1);

  public nsISVGRendererRegion createRectRegion(float arg1, float arg2, float arg3, float arg4);

}
