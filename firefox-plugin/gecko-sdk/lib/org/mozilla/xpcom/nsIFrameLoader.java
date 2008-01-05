/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIFrameLoader">
 **/

package org.mozilla.xpcom;

public interface nsIFrameLoader extends nsISupports
{
  public static final String NS_IFRAMELOADER_IID =
    "{88800e93-c6af-4d69-9ee0-29c1100ff431}";

  public nsIDocShell getDocShell();

  public void loadFrame();

  public void destroy();

  public boolean getDepthTooGreat();

}
