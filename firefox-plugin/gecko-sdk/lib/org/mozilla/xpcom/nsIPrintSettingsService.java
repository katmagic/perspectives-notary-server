/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIPrintSettingsSer">
 **/

package org.mozilla.xpcom;

public interface nsIPrintSettingsService extends nsISupports
{
  public static final String NS_IPRINTSETTINGSSERVICE_IID =
    "{841387c8-72e6-484b-9296-bf6eea80d58a}";

  public nsIPrintSettings getGlobalPrintSettings();

  public nsIPrintSettings getNewPrintSettings();

  public String getDefaultPrinterName();

  public void initPrintSettingsFromPrinter(String arg1, nsIPrintSettings arg2);

  public void initPrintSettingsFromPrefs(nsIPrintSettings arg1, boolean arg2, long arg3);

  public void savePrintSettingsToPrefs(nsIPrintSettings arg1, boolean arg2, long arg3);

}
