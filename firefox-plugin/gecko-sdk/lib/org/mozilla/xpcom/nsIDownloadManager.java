/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIDownloadManager">
 **/

package org.mozilla.xpcom;

public interface nsIDownloadManager extends nsISupports
{
  public static final String NS_IDOWNLOADMANAGER_IID =
    "{1f280341-30f4-4009-bb0d-a78f2936d1fb}";

  public static final short DOWNLOAD_NOTSTARTED = -1;

  public static final short DOWNLOAD_DOWNLOADING = 0;

  public static final short DOWNLOAD_FINISHED = 1;

  public static final short DOWNLOAD_FAILED = 2;

  public static final short DOWNLOAD_CANCELED = 3;

  public static final short DOWNLOAD_PAUSED = 4;

  public static final short DOWNLOAD_TYPE_DOWNLOAD = 0;

  public nsIDownload addDownload(short arg1, nsIURI arg2, nsIURI arg3, String arg4, String arg5, nsIMIMEInfo arg6, double arg7, nsILocalFile arg8, nsICancelable arg9);

  public nsIDownload getDownload(String arg1);

  public void cancelDownload(String arg1);

  public void removeDownload(String arg1);

  public void pauseDownload(String arg1);

  public void resumeDownload(String arg1);

  public void open(nsIDOMWindow arg1, String arg2);

  public nsIDownloadProgressListener getListener();

  public void setListener(nsIDownloadProgressListener arg1);

  public void startBatchUpdate();

  public void endBatchUpdate();

  public boolean getCanCleanUp();

  public void cleanUp();

  public int getActiveDownloadCount();

  public nsISupportsArray getActiveDownloads();

  public void saveState();

  public void flush();

  public nsIRDFDataSource getDatasource();

}
