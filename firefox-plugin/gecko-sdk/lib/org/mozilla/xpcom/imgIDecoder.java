/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+imgIDecoder">
 **/

package org.mozilla.xpcom;

public interface imgIDecoder extends nsISupports
{
  public static final String IMGIDECODER_IID =
    "{9eebf43a-1dd1-11b2-953e-f1782f4cbad3}";

  public void init(imgILoad arg1);

  public void close();

  public void flush();

  public long writeFrom(nsIInputStream arg1, long arg2);

}
