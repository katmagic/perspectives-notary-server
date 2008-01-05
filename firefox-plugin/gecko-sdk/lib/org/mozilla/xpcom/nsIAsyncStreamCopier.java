/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIAsyncStreamCopie">
 **/

package org.mozilla.xpcom;

public interface nsIAsyncStreamCopier extends nsIRequest
{
  public static final String NS_IASYNCSTREAMCOPIER_IID =
    "{eaa49141-c21c-4fe8-a79b-77860a3910aa}";

  public void init(nsIInputStream arg1, nsIOutputStream arg2, nsIEventTarget arg3, boolean arg4, boolean arg5, long arg6);

  public void asyncCopy(nsIRequestObserver arg1, nsISupports arg2);

}
