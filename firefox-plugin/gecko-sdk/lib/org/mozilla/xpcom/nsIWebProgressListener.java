/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIWebProgressListe">
 **/

package org.mozilla.xpcom;

public interface nsIWebProgressListener extends nsISupports
{
  public static final String NS_IWEBPROGRESSLISTENER_IID =
    "{570f39d1-efd0-11d3-b093-00a024ffc08c}";

  public static final long STATE_START = 1L;

  public static final long STATE_REDIRECTING = 2L;

  public static final long STATE_TRANSFERRING = 4L;

  public static final long STATE_NEGOTIATING = 8L;

  public static final long STATE_STOP = 16L;

  public static final long STATE_IS_REQUEST = 65536L;

  public static final long STATE_IS_DOCUMENT = 131072L;

  public static final long STATE_IS_NETWORK = 262144L;

  public static final long STATE_IS_WINDOW = 524288L;

  public static final long STATE_RESTORING = 16777216L;

  public static final long STATE_IS_INSECURE = 4L;

  public static final long STATE_IS_BROKEN = 1L;

  public static final long STATE_IS_SECURE = 2L;

  public static final long STATE_SECURE_HIGH = 262144L;

  public static final long STATE_SECURE_MED = 65536L;

  public static final long STATE_SECURE_LOW = 131072L;

  public void onStateChange(nsIWebProgress arg1, nsIRequest arg2, long arg3, long arg4);

  public void onProgressChange(nsIWebProgress arg1, nsIRequest arg2, int arg3, int arg4, int arg5, int arg6);

  public void onLocationChange(nsIWebProgress arg1, nsIRequest arg2, nsIURI arg3);

  public void onStatusChange(nsIWebProgress arg1, nsIRequest arg2, long arg3, String arg4);

  public void onSecurityChange(nsIWebProgress arg1, nsIRequest arg2, long arg3);

}
