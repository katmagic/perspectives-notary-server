/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsITransport">
 **/

package org.mozilla.xpcom;

public interface nsITransport extends nsISupports
{
  public static final String NS_ITRANSPORT_IID =
    "{cbb0baeb-5fcb-408b-a2be-9f8fc98d0af1}";

  public static final long OPEN_BLOCKING = 1L;

  public static final long OPEN_UNBUFFERED = 2L;

  public static final long STATUS_READING = 2152398856L;

  public static final long STATUS_WRITING = 2152398857L;

  public nsIInputStream openInputStream(long arg1, long arg2, long arg3);

  public nsIOutputStream openOutputStream(long arg1, long arg2, long arg3);

  public void close(long arg1);

  public void setEventSink(nsITransportEventSink arg1, nsIEventTarget arg2);

}
