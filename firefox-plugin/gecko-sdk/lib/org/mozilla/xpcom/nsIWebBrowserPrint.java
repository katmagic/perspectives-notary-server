/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIWebBrowserPrint">
 **/

package org.mozilla.xpcom;

public interface nsIWebBrowserPrint extends nsISupports
{
  public static final String NS_IWEBBROWSERPRINT_IID =
    "{9a7ca4b0-fbba-11d4-a869-00105a183419}";

  public static final short PRINTPREVIEW_GOTO_PAGENUM = 0;

  public static final short PRINTPREVIEW_PREV_PAGE = 1;

  public static final short PRINTPREVIEW_NEXT_PAGE = 2;

  public static final short PRINTPREVIEW_HOME = 3;

  public static final short PRINTPREVIEW_END = 4;

  public nsIPrintSettings getGlobalPrintSettings();

  public nsIPrintSettings getCurrentPrintSettings();

  public nsIDOMWindow getCurrentChildDOMWindow();

  public boolean getDoingPrint();

  public boolean getDoingPrintPreview();

  public boolean getIsFramesetDocument();

  public boolean getIsFramesetFrameSelected();

  public boolean getIsIFrameSelected();

  public boolean getIsRangeSelection();

  public int getPrintPreviewNumPages();

  public void print(nsIPrintSettings arg1, nsIWebProgressListener arg2);

  public void printPreview(nsIPrintSettings arg1, nsIDOMWindow arg2, nsIWebProgressListener arg3);

  public void printPreviewNavigate(short arg1, int arg2);

  public void cancel();

  public String[] enumerateDocumentNames(long[] arg1);

  public void exitPrintPreview();

}
