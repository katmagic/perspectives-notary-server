/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIDownloadProgress">
 **/

package org.mozilla.xpcom;

public interface nsIDownloadProgressListener extends nsISupports
{
  public static final String NS_IDOWNLOADPROGRESSLISTENER_IID =
    "{8b193f0a-cf0c-4b5f-b4e3-a388df6f07b2}";

  public nsIDOMDocument getDocument();

  public void setDocument(nsIDOMDocument arg1);

  public void onStateChange(nsIWebProgress arg1, nsIRequest arg2, long arg3, long arg4, nsIDownload arg5);

  public void onProgressChange(nsIWebProgress arg1, nsIRequest arg2, long arg3, long arg4, long arg5, long arg6, nsIDownload arg7);

  public void onStatusChange(nsIWebProgress arg1, nsIRequest arg2, long arg3, String arg4, nsIDownload arg5);

  public void onLocationChange(nsIWebProgress arg1, nsIRequest arg2, nsIURI arg3, nsIDownload arg4);

  public void onSecurityChange(nsIWebProgress arg1, nsIRequest arg2, long arg3, nsIDownload arg4);

}
