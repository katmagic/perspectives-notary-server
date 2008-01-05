/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIGlobalHistory2">
 **/

package org.mozilla.xpcom;

public interface nsIGlobalHistory2 extends nsISupports
{
  public static final String NS_IGLOBALHISTORY2_IID =
    "{cf777d42-1270-4b34-be7b-2931c93feda5}";

  public void addURI(nsIURI arg1, boolean arg2, boolean arg3, nsIURI arg4);

  public boolean isVisited(nsIURI arg1);

  public void setPageTitle(nsIURI arg1, String arg2);

}
