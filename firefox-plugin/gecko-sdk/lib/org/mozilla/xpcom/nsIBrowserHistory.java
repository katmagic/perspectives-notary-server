/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIBrowserHistory">
 **/

package org.mozilla.xpcom;

public interface nsIBrowserHistory extends nsIGlobalHistory2
{
  public static final String NS_IBROWSERHISTORY_IID =
    "{c43079c3-3d8d-4b7c-af14-0e30ab46865f}";

  public void addPageWithDetails(nsIURI arg1, String arg2, long arg3);

  public String getLastPageVisited();

  public long getCount();

  public void removePage(nsIURI arg1);

  public void removePagesFromHost(String arg1, boolean arg2);

  public void removeAllPages();

  public void hidePage(nsIURI arg1);

  public void markPageAsTyped(nsIURI arg1);

}
