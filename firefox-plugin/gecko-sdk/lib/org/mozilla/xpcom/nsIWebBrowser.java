/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIWebBrowser">
 **/

package org.mozilla.xpcom;

public interface nsIWebBrowser extends nsISupports
{
  public static final String NS_IWEBBROWSER_IID =
    "{69e5df00-7b8b-11d3-af61-00a024ffc08c}";

  public void addWebBrowserListener(nsISupports arg1, String arg2);

  public void removeWebBrowserListener(nsISupports arg1, String arg2);

  public nsIWebBrowserChrome getContainerWindow();

  public void setContainerWindow(nsIWebBrowserChrome arg1);

  public nsIURIContentListener getParentURIContentListener();

  public void setParentURIContentListener(nsIURIContentListener arg1);

  public nsIDOMWindow getContentDOMWindow();

}
