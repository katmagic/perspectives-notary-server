/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIProgressDialog">
 **/

package org.mozilla.xpcom;

public interface nsIProgressDialog extends nsIDownload
{
  public static final String NS_IPROGRESSDIALOG_IID =
    "{20e790a2-76c6-462d-851a-22ab6cbbe48b}";

  public void open(nsIDOMWindow arg1);

  public boolean getCancelDownloadOnClose();

  public void setCancelDownloadOnClose(boolean arg1);

  public nsIObserver getObserver();

  public void setObserver(nsIObserver arg1);

  public nsIDOMWindow getDialog();

  public void setDialog(nsIDOMWindow arg1);

}
