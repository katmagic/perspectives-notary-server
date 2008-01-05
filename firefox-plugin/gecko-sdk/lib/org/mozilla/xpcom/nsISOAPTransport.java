/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsISOAPTransport">
 **/

package org.mozilla.xpcom;

public interface nsISOAPTransport extends nsISupports
{
  public static final String NS_ISOAPTRANSPORT_IID =
    "{99ec6695-535f-11d4-9a58-000064657374}";

  public void syncCall(nsISOAPCall arg1, nsISOAPResponse arg2);

  public nsISOAPCallCompletion asyncCall(nsISOAPCall arg1, nsISOAPResponseListener arg2, nsISOAPResponse arg3);

  public void addListener(nsISOAPTransportListener arg1, boolean arg2);

  public void removeListener(nsISOAPTransportListener arg1, boolean arg2);

}
