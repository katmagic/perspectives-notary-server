/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsISVGRendererGlyph">
 **/

package org.mozilla.xpcom;

public interface nsISVGRendererGlyphGeometry extends nsISupports
{
  public static final String NS_ISVGRENDERERGLYPHGEOMETRY_IID =
    "{cd302675-b093-4018-8081-3e65af962aa8}";

  public void render(nsISVGRendererCanvas arg1);

  public nsISVGRendererRegion update(long arg1);

  public nsISVGRendererRegion getCoveredRegion();

  public boolean containsPoint(float arg1, float arg2);

}
