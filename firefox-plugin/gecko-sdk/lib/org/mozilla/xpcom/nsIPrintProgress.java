/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIPrintProgress">
 **/

package org.mozilla.xpcom;

public interface nsIPrintProgress extends nsIWebProgressListener
{
  public static final String NS_IPRINTPROGRESS_IID =
    "{7e46bc35-fb7d-4b45-ab35-82fd61015380}";

  public void openProgressDialog(nsIDOMWindowInternal arg1, String arg2, nsISupports arg3, nsIObserver arg4, boolean[] arg5);

  public void closeProgressDialog(boolean arg1);

  public void registerListener(nsIWebProgressListener arg1);

  public void unregisterListener(nsIWebProgressListener arg1);

  public void doneIniting();

  public nsIPrompt getPrompter();

  public boolean getProcessCanceledByUser();

  public void setProcessCanceledByUser(boolean arg1);

}
