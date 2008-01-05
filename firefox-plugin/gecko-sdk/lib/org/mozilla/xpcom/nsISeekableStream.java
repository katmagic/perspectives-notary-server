/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsISeekableStream">
 **/

package org.mozilla.xpcom;

public interface nsISeekableStream extends nsISupports
{
  public static final String NS_ISEEKABLESTREAM_IID =
    "{8429d350-1040-4661-8b71-f2a6ba455980}";

  public static final int NS_SEEK_SET = 0;

  public static final int NS_SEEK_CUR = 1;

  public static final int NS_SEEK_END = 2;

  public void seek(int arg1, long arg2);

  public long tell();

  public void setEOF();

}
