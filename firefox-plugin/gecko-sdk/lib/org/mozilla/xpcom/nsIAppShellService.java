/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIAppShellService">
 **/

package org.mozilla.xpcom;

public interface nsIAppShellService extends nsISupports
{
  public static final String NS_IAPPSHELLSERVICE_IID =
    "{93a28ba2-7e22-11d9-9b6f-000a95d535fa}";

  public static final int SIZE_TO_CONTENT = -1;

  public nsIXULWindow createTopLevelWindow(nsIXULWindow arg1, nsIURI arg2, long arg3, int arg4, int arg5, nsISupports arg6);

  public void destroyHiddenWindow();

  public nsIXULWindow getHiddenWindow();

  public nsIDOMWindowInternal getHiddenDOMWindow();

  public void registerTopLevelWindow(nsIXULWindow arg1);

  public void unregisterTopLevelWindow(nsIXULWindow arg1);

  public void topLevelWindowIsModal(nsIXULWindow arg1, boolean arg2);

}
