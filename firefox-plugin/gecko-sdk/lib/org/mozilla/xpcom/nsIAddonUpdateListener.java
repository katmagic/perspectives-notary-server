/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIAddonUpdateListe">
 **/

package org.mozilla.xpcom;

public interface nsIAddonUpdateListener extends nsISupports
{
  public static final String NS_IADDONUPDATELISTENER_IID =
    "{bb86037c-98c1-4c22-8e03-1e4c9fc89a8e}";

  public void onStateChange(nsIUpdateItem arg1, short arg2, int arg3);

  public void onProgress(nsIUpdateItem arg1, long arg2, long arg3);

}
