/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIMultiplexInputSt">
 **/

package org.mozilla.xpcom;

public interface nsIMultiplexInputStream extends nsIInputStream
{
  public static final String NS_IMULTIPLEXINPUTSTREAM_IID =
    "{a076fd12-1dd1-11b2-b19a-d53b5dffaade}";

  public long getCount();

  public void appendStream(nsIInputStream arg1);

  public void insertStream(nsIInputStream arg1, long arg2);

  public void removeStream(long arg1);

  public nsIInputStream getStream(long arg1);

}
