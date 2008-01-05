/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIUpdateCheckListe">
 **/

package org.mozilla.xpcom;

public interface nsIUpdateCheckListener extends nsISupports
{
  public static final String NS_IUPDATECHECKLISTENER_IID =
    "{8cbceb6e-8e27-46f2-8808-444c6499f836}";

  public void onProgress(nsIXMLHttpRequest arg1, long arg2, long arg3);

  public void onCheckComplete(nsIXMLHttpRequest arg1, nsIUpdate[] arg2, long arg3);

  public void onError(nsIXMLHttpRequest arg1, nsIUpdate arg2);

}
