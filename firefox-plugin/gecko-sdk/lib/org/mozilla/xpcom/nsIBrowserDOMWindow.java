/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIBrowserDOMWindow">
 **/

package org.mozilla.xpcom;

public interface nsIBrowserDOMWindow extends nsISupports
{
  public static final String NS_IBROWSERDOMWINDOW_IID =
    "{af25c296-aaec-4f7f-8885-dd37a1cc0a13}";

  public static final short OPEN_DEFAULTWINDOW = 0;

  public static final short OPEN_CURRENTWINDOW = 1;

  public static final short OPEN_NEWWINDOW = 2;

  public static final short OPEN_NEWTAB = 3;

  public static final short OPEN_EXTERNAL = 1;

  public static final short OPEN_NEW = 2;

  public nsIDOMWindow openURI(nsIURI arg1, nsIDOMWindow arg2, short arg3, short arg4);

  public boolean isTabContentWindow(nsIDOMWindow arg1);

}
