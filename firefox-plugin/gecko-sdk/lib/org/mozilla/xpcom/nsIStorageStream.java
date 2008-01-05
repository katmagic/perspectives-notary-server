/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIStorageStream">
 **/

package org.mozilla.xpcom;

public interface nsIStorageStream extends nsISupports
{
  public static final String NS_ISTORAGESTREAM_IID =
    "{604ad9d0-753e-11d3-90ca-34278643278f}";

  public void init(long arg1, long arg2, nsIMemory arg3);

  public nsIOutputStream getOutputStream(int arg1);

  public nsIInputStream newInputStream(int arg1);

  public long getLength();

  public void setLength(long arg1);

  public boolean getWriteInProgress();

}
