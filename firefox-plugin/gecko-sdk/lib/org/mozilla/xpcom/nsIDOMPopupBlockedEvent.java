/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIDOMPopupBlockedE">
 **/

package org.mozilla.xpcom;

public interface nsIDOMPopupBlockedEvent extends nsIDOMEvent
{
  public static final String NS_IDOMPOPUPBLOCKEDEVENT_IID =
    "{9e201104-78e9-4cb3-aff5-7f0a9cf446c0}";

  public nsIURI getRequestingWindowURI();

  public nsIURI getPopupWindowURI();

  public String getPopupWindowFeatures();

  public void initPopupBlockedEvent(String arg1, boolean arg2, boolean arg3, nsIURI arg4, nsIURI arg5, String arg6);

}
