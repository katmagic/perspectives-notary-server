/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIWindowWatcher">
 **/

package org.mozilla.xpcom;

public interface nsIWindowWatcher extends nsISupports
{
  public static final String NS_IWINDOWWATCHER_IID =
    "{002286a8-494b-43b3-8ddd-49e3fc50622b}";

  public nsIDOMWindow openWindow(nsIDOMWindow arg1, String arg2, String arg3, String arg4, nsISupports arg5);

  public void registerNotification(nsIObserver arg1);

  public void unregisterNotification(nsIObserver arg1);

  public nsISimpleEnumerator getWindowEnumerator();

  public nsIPrompt getNewPrompter(nsIDOMWindow arg1);

  public nsIAuthPrompt getNewAuthPrompter(nsIDOMWindow arg1);

  public void setWindowCreator(nsISupports arg1);

  public nsIWebBrowserChrome getChromeForWindow(nsIDOMWindow arg1);

  public nsIDOMWindow getWindowByName(String arg1, nsIDOMWindow arg2);

  public nsIDOMWindow getActiveWindow();

  public void setActiveWindow(nsIDOMWindow arg1);

}
