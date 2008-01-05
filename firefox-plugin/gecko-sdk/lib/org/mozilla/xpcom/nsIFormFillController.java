/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIFormFillControll">
 **/

package org.mozilla.xpcom;

public interface nsIFormFillController extends nsISupports
{
  public static final String NS_IFORMFILLCONTROLLER_IID =
    "{872f07f3-ed11-47c6-b7cf-246db53379fb}";

  public void attachToBrowser(nsIDocShell arg1, nsIAutoCompletePopup arg2);

  public void detachFromBrowser(nsIDocShell arg1);

}
