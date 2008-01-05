/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIDownloadObserver">
 **/

package org.mozilla.xpcom;

public interface nsIDownloadObserver extends nsISupports
{
  public static final String NS_IDOWNLOADOBSERVER_IID =
    "{44b3153e-a54e-4077-a527-b0325e40924e}";

  public void onDownloadComplete(nsIDownloader arg1, nsIRequest arg2, nsISupports arg3, long arg4, nsIFile arg5);

}
