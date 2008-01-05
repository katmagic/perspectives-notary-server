/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIPrintingPromptSe">
 **/

package org.mozilla.xpcom;

public interface nsIPrintingPromptService extends nsISupports
{
  public static final String NS_IPRINTINGPROMPTSERVICE_IID =
    "{75d1553d-63bf-4b5d-a8f7-e4e4cac21ba4}";

  public void showPrintDialog(nsIDOMWindow arg1, nsIWebBrowserPrint arg2, nsIPrintSettings arg3);

  public void showProgress(nsIDOMWindow arg1, nsIWebBrowserPrint arg2, nsIPrintSettings arg3, nsIObserver arg4, boolean arg5, nsIWebProgressListener[] arg6, nsIPrintProgressParams[] arg7, boolean[] arg8);

  public void showPageSetup(nsIDOMWindow arg1, nsIPrintSettings arg2, nsIObserver arg3);

  public void showPrinterProperties(nsIDOMWindow arg1, String arg2, nsIPrintSettings arg3);

}
