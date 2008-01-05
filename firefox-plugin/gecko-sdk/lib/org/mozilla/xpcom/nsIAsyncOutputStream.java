/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIAsyncOutputStrea">
 **/

package org.mozilla.xpcom;

public interface nsIAsyncOutputStream extends nsIOutputStream
{
  public static final String NS_IASYNCOUTPUTSTREAM_IID =
    "{10dc9c94-8aff-49c6-8af9-d7fdb7339dae}";

  public static final long WAIT_CLOSURE_ONLY = 1L;

  public void closeWithStatus(long arg1);

  public void asyncWait(nsIOutputStreamCallback arg1, long arg2, long arg3, nsIEventTarget arg4);

}
