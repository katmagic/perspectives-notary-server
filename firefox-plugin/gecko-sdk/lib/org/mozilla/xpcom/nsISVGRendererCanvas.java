/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsISVGRendererCanva">
 **/

package org.mozilla.xpcom;

public interface nsISVGRendererCanvas extends nsISupports
{
  public static final String NS_ISVGRENDERERCANVAS_IID =
    "{2e64a227-de4b-4a69-ab82-5dda1579e90f}";

  public static final int SVG_RENDER_MODE_NORMAL = 0;

  public static final int SVG_RENDER_MODE_CLIP = 1;

  public void unlockRenderingContext();

  public nsISupports getPresContext();

  public void clear(long arg1);

  public void flush();

  public int getRenderMode();

  public void setRenderMode(int arg1);

  public void pushClip();

  public void popClip();

  public void setClipRect(nsIDOMSVGMatrix arg1, float arg2, float arg3, float arg4, float arg5);

  public void pushSurface(nsISupports arg1);

  public void popSurface();

  public void compositeSurface(nsISupports arg1, long arg2, long arg3, float arg4);

  public void compositeSurfaceMatrix(nsISupports arg1, nsIDOMSVGMatrix arg2, float arg3);

}
