/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIUpdatePrompt">
 **/

package org.mozilla.xpcom;

public interface nsIUpdatePrompt extends nsISupports
{
  public static final String NS_IUPDATEPROMPT_IID =
    "{22b00276-ec23-4034-a764-395da539b4be}";

  public void checkForUpdates();

  public void showUpdateAvailable(nsIUpdate arg1);

  public void showUpdateDownloaded(nsIUpdate arg1);

  public void showUpdateInstalled(nsIUpdate arg1);

  public void showUpdateError(nsIUpdate arg1);

  public void showUpdateHistory(nsIDOMWindow arg1);

}
