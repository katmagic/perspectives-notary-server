/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIRequestObserver">
 **/

package org.mozilla.xpcom;

public interface nsIRequestObserver extends nsISupports
{
  public static final String NS_IREQUESTOBSERVER_IID =
    "{fd91e2e0-1481-11d3-9333-00104ba0fd40}";

  public void onStartRequest(nsIRequest arg1, nsISupports arg2);

  public void onStopRequest(nsIRequest arg1, nsISupports arg2, long arg3);

}
