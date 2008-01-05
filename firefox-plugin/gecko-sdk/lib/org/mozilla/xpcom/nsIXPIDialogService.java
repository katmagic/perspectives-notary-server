/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIXPIDialogService">
 **/

package org.mozilla.xpcom;

public interface nsIXPIDialogService extends nsISupports
{
  public static final String NS_IXPIDIALOGSERVICE_IID =
    "{8cdd8baa-1dd2-11b2-909a-f0178da5c5ff}";

  public boolean confirmInstall(nsIDOMWindow arg1, String[] arg2, long arg3);

  public void openProgressDialog(String[] arg1, long arg2, nsIObserver arg3);

}
