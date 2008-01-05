/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIPrintOptions">
 **/

package org.mozilla.xpcom;

public interface nsIPrintOptions extends nsISupports
{
  public static final String NS_IPRINTOPTIONS_IID =
    "{d9948a4d-f49c-4456-938a-acda2c8d7741}";

  public static final short kNativeDataPrintRecord = 0;

  public void showPrintSetupDialog(nsIPrintSettings arg1);

  public nsIPrintSettings createPrintSettings();

  public nsISimpleEnumerator availablePrinters();

  public int getPrinterPrefInt(nsIPrintSettings arg1, String arg2);

  public void displayJobProperties(String arg1, nsIPrintSettings arg2, boolean[] arg3);

  public void setFontNamePointSize(String arg1, int arg2);

}
