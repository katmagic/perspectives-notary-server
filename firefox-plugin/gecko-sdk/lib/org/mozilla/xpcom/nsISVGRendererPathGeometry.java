/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsISVGRendererPathG">
 **/

package org.mozilla.xpcom;

public interface nsISVGRendererPathGeometry extends nsISupports
{
  public static final String NS_ISVGRENDERERPATHGEOMETRY_IID =
    "{1e4a2bc7-96e6-4c4d-80a6-e284cec9e3aa}";

  public void render(nsISVGRendererCanvas arg1);

  public nsISVGRendererRegion update(long arg1);

  public nsISVGRendererRegion getCoveredRegion();

  public boolean containsPoint(float arg1, float arg2);

  public nsIDOMSVGRect getBoundingBox();

}
