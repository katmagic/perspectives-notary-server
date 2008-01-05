/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIScreen">
 **/

package org.mozilla.xpcom;

public interface nsIScreen extends nsISupports
{
  public static final String NS_ISCREEN_IID =
    "{f728830e-1dd1-11b2-9598-fb9f414f2465}";

  public void getRect(int[] arg1, int[] arg2, int[] arg3, int[] arg4);

  public void getAvailRect(int[] arg1, int[] arg2, int[] arg3, int[] arg4);

  public int getPixelDepth();

  public int getColorDepth();

}
