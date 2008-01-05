/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIChannelEventSink">
 **/

package org.mozilla.xpcom;

public interface nsIChannelEventSink extends nsISupports
{
  public static final String NS_ICHANNELEVENTSINK_IID =
    "{6757d790-2916-498e-aaca-6b668a956875}";

  public static final long REDIRECT_TEMPORARY = 1L;

  public static final long REDIRECT_PERMANENT = 2L;

  public static final long REDIRECT_INTERNAL = 4L;

  public void onChannelRedirect(nsIChannel arg1, nsIChannel arg2, long arg3);

}
