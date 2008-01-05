/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIPrinterEnumerato">
 **/

package org.mozilla.xpcom;

public interface nsIPrinterEnumerator extends nsISupports
{
  public static final String NS_IPRINTERENUMERATOR_IID =
    "{a6cf9128-15b3-11d2-932e-00805f8add32}";

  public String getDefaultPrinterName();

  public void initPrintSettingsFromPrinter(String arg1, nsIPrintSettings arg2);

  public String[] enumeratePrinters(long[] arg1);

  public void displayPropertiesDlg(String arg1, nsIPrintSettings arg2);

}
