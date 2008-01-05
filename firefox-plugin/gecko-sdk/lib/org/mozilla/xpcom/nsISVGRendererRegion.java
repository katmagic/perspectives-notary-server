/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsISVGRendererRegio">
 **/

package org.mozilla.xpcom;

public interface nsISVGRendererRegion extends nsISupports
{
  public static final String NS_ISVGRENDERERREGION_IID =
    "{9356e1c6-66e6-49a0-8c67-7e910270ed1e}";

  public nsISVGRendererRegion combine(nsISVGRendererRegion arg1);

  public void getRectangleScans(nsISVGRectangleSink arg1);

}
