/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIPipe">
 **/

package org.mozilla.xpcom;

public interface nsIPipe extends nsISupports
{
  public static final String NS_IPIPE_IID =
    "{f4211abc-61b3-11d4-9877-00c04fa0cf4a}";

  public void init(boolean arg1, boolean arg2, long arg3, long arg4, nsIMemory arg5);

  public nsIAsyncInputStream getInputStream();

  public nsIAsyncOutputStream getOutputStream();

}
