/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIHelperAppLaunche">
 **/

package org.mozilla.xpcom;

public interface nsIHelperAppLauncherDialog extends nsISupports
{
  public static final String NS_IHELPERAPPLAUNCHERDIALOG_IID =
    "{64355793-988d-40a5-ba8e-fcde78cac631}";

  public static final long REASON_CANTHANDLE = 0L;

  public static final long REASON_SERVERREQUEST = 1L;

  public static final long REASON_TYPESNIFFED = 2L;

  public void show(nsIHelperAppLauncher arg1, nsISupports arg2, long arg3);

  public nsILocalFile promptForSaveToFile(nsIHelperAppLauncher arg1, nsISupports arg2, String arg3, String arg4);

}
