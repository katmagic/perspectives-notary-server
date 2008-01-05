/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsITransportEventSi">
 **/

package org.mozilla.xpcom;

public interface nsITransportEventSink extends nsISupports
{
  public static final String NS_ITRANSPORTEVENTSINK_IID =
    "{eda4f520-67f7-484b-a691-8c3226a5b0a6}";

  public void onTransportStatus(nsITransport arg1, long arg2, double arg3, double arg4);

}
