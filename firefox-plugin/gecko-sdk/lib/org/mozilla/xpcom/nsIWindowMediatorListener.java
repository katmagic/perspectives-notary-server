/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIWindowMediatorLi">
 **/

package org.mozilla.xpcom;

public interface nsIWindowMediatorListener extends nsISupports
{
  public static final String NS_IWINDOWMEDIATORLISTENER_IID =
    "{2f276982-0d60-4377-a595-d350ba516395}";

  public void onWindowTitleChange(nsIXULWindow arg1, String arg2);

  public void onOpenWindow(nsIXULWindow arg1);

  public void onCloseWindow(nsIXULWindow arg1);

}
