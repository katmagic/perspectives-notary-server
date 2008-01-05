/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIDOMChromeWindow">
 **/

package org.mozilla.xpcom;

public interface nsIDOMChromeWindow extends nsISupports
{
  public static final String NS_IDOMCHROMEWINDOW_IID =
    "{445fa0fc-2151-4cb4-83d3-34c3e39453de}";

  public static final int STATE_MAXIMIZED = 1;

  public static final int STATE_MINIMIZED = 2;

  public static final int STATE_NORMAL = 3;

  public String getTitle();

  public void setTitle(String arg1);

  public int getWindowState();

  public nsIBrowserDOMWindow getBrowserDOMWindow();

  public void setBrowserDOMWindow(nsIBrowserDOMWindow arg1);

  public void getAttention();

  public void getAttentionWithCycleCount(int arg1);

  public void setCursor(String arg1);

  public void maximize();

  public void minimize();

  public void restore();

}
