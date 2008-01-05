/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIApplicationUpdat">
 **/

package org.mozilla.xpcom;

public interface nsIApplicationUpdateService extends nsISupports
{
  public static final String NS_IAPPLICATIONUPDATESERVICE_IID =
    "{9849c4bf-5197-4d22-baa8-e3b44a1703d2}";

  public nsIUpdateChecker getBackgroundChecker();

  public nsIUpdate selectUpdate(nsIUpdate[] arg1, long arg2);

  public void addDownloadListener(nsIRequestObserver arg1);

  public void removeDownloadListener(nsIRequestObserver arg1);

  public String downloadUpdate(nsIUpdate arg1, boolean arg2);

  public void pauseDownload();

  public boolean getIsDownloading();

  public boolean getCanUpdate();

}
