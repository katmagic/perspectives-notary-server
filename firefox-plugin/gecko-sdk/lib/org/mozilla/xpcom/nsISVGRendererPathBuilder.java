/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsISVGRendererPathB">
 **/

package org.mozilla.xpcom;

public interface nsISVGRendererPathBuilder extends nsISupports
{
  public static final String NS_ISVGRENDERERPATHBUILDER_IID =
    "{c3cd294e-39ae-4718-b2bc-87c0fad97a12}";

  public void moveto(float arg1, float arg2);

  public void lineto(float arg1, float arg2);

  public void curveto(float arg1, float arg2, float arg3, float arg4, float arg5, float arg6);

  public void arcto(float arg1, float arg2, float arg3, float arg4, float arg5, boolean arg6, boolean arg7);

  public void closePath(float[] arg1, float[] arg2);

  public void endPath();

}
