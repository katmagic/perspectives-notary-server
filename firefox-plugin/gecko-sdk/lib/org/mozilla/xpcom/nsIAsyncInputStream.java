/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIAsyncInputStream">
 **/

package org.mozilla.xpcom;

public interface nsIAsyncInputStream extends nsIInputStream
{
  public static final String NS_IASYNCINPUTSTREAM_IID =
    "{15a15329-00de-44e8-ab06-0d0b0d43dc5b}";

  public static final long WAIT_CLOSURE_ONLY = 1L;

  public void closeWithStatus(long arg1);

  public void asyncWait(nsIInputStreamCallback arg1, long arg2, long arg3, nsIEventTarget arg4);

}
