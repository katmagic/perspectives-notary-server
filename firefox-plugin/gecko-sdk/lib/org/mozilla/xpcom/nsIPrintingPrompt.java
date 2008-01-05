/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIPrintingPrompt">
 **/

package org.mozilla.xpcom;

public interface nsIPrintingPrompt extends nsISupports
{
  public static final String NS_IPRINTINGPROMPT_IID =
    "{44e314ca-75b1-4f3d-9553-9b3507912108}";

  public void showPrintDialog(nsIWebBrowserPrint arg1, nsIPrintSettings arg2);

  public void showProgress(nsIWebBrowserPrint arg1, nsIPrintSettings arg2, nsIObserver arg3, boolean arg4, nsIWebProgressListener[] arg5, nsIPrintProgressParams[] arg6, boolean[] arg7);

  public void showPageSetup(nsIPrintSettings arg1, nsIObserver arg2);

  public void showPrinterProperties(String arg1, nsIPrintSettings arg2);

}
