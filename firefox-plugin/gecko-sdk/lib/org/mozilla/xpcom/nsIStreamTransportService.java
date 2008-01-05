/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIStreamTransportS">
 **/

package org.mozilla.xpcom;

public interface nsIStreamTransportService extends nsISupports
{
  public static final String NS_ISTREAMTRANSPORTSERVICE_IID =
    "{8268d474-efbf-494f-a152-e8a8616f4e52}";

  public nsITransport createInputTransport(nsIInputStream arg1, long arg2, long arg3, boolean arg4);

  public nsITransport createOutputTransport(nsIOutputStream arg1, long arg2, long arg3, boolean arg4);

}
