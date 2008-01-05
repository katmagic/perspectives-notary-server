/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIXPIProgressDialo">
 **/

package org.mozilla.xpcom;

public interface nsIXPIProgressDialog extends nsISupports
{
  public static final String NS_IXPIPROGRESSDIALOG_IID =
    "{ce8f744e-d5a5-41b3-911f-0fee3008b64e}";

  public static final short DOWNLOAD_START = 0;

  public static final short DOWNLOAD_DONE = 1;

  public static final short INSTALL_START = 2;

  public static final short INSTALL_DONE = 3;

  public static final short DIALOG_CLOSE = 4;

  public void onStateChange(long arg1, short arg2, int arg3);

  public void onProgress(long arg1, double arg2, double arg3);

}
