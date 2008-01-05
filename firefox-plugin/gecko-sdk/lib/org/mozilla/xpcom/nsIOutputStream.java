/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIOutputStream">
 **/

package org.mozilla.xpcom;

public interface nsIOutputStream extends nsISupports
{
  public static final String NS_IOUTPUTSTREAM_IID =
    "{0d0acd2a-61b4-11d4-9877-00c04fa0cf4a}";

  public void close();

  public void flush();

  public long write(String arg1, long arg2);

  public long writeFrom(nsIInputStream arg1, long arg2);

  public boolean isNonBlocking();

}
