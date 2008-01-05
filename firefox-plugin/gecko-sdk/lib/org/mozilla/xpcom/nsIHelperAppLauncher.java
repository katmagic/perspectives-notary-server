/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIHelperAppLaunche">
 **/

package org.mozilla.xpcom;

public interface nsIHelperAppLauncher extends nsICancelable
{
  public static final String NS_IHELPERAPPLAUNCHER_IID =
    "{99a0882d-2ff9-4659-9952-9ac531ba5592}";

  public nsIMIMEInfo getMIMEInfo();

  public nsIURI getSource();

  public String getSuggestedFileName();

  public void saveToDisk(nsIFile arg1, boolean arg2);

  public void launchWithApplication(nsIFile arg1, boolean arg2);

  public void setWebProgressListener(nsIWebProgressListener2 arg1);

  public void closeProgressWindow();

  public nsIFile getTargetFile();

  public double getTimeDownloadStarted();

}
