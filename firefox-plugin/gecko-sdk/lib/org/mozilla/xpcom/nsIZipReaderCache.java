/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIZipReaderCache">
 **/

package org.mozilla.xpcom;

public interface nsIZipReaderCache extends nsISupports
{
  public static final String NS_IZIPREADERCACHE_IID =
    "{52c45d86-0cc3-11d4-986e-00c04fa0cf4a}";

  public void init(long arg1);

  public nsIZipReader getZip(nsIFile arg1);

}
