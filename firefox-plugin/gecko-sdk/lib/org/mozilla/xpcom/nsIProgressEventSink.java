/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIProgressEventSin">
 **/

package org.mozilla.xpcom;

public interface nsIProgressEventSink extends nsISupports
{
  public static final String NS_IPROGRESSEVENTSINK_IID =
    "{d974c99e-4148-4df9-8d98-de834a2f6462}";

  public void onProgress(nsIRequest arg1, nsISupports arg2, double arg3, double arg4);

  public void onStatus(nsIRequest arg1, nsISupports arg2, long arg3, String arg4);

}
