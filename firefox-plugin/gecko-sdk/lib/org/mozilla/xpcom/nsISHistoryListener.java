/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsISHistoryListener">
 **/

package org.mozilla.xpcom;

public interface nsISHistoryListener extends nsISupports
{
  public static final String NS_ISHISTORYLISTENER_IID =
    "{3b07f591-e8e1-11d4-9882-00c04fa02f40}";

  public void onHistoryNewEntry(nsIURI arg1);

  public boolean onHistoryGoBack(nsIURI arg1);

  public boolean onHistoryGoForward(nsIURI arg1);

  public boolean onHistoryReload(nsIURI arg1, long arg2);

  public boolean onHistoryGotoIndex(int arg1, nsIURI arg2);

  public boolean onHistoryPurge(int arg1);

}
