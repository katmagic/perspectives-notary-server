/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsINativeAppSupport">
 **/

package org.mozilla.xpcom;

public interface nsINativeAppSupport extends nsISupports
{
  public static final String NS_INATIVEAPPSUPPORT_IID =
    "{5fdf8480-1f98-11d4-8077-00600811a9c3}";

  public boolean start();

  public void enable();

  public boolean stop();

  public void quit();

  public void onLastWindowClosing();

  public void reOpen();

}
