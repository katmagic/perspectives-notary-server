/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIFullScreen">
 **/

package org.mozilla.xpcom;

public interface nsIFullScreen extends nsISupports
{
  public static final String NS_IFULLSCREEN_IID =
    "{9854976e-1dd1-11b2-8350-e6d35099fbce}";

  public void hideAllOSChrome();

  public void showAllOSChrome();

  public nsISimpleEnumerator getChromeItems();

}
