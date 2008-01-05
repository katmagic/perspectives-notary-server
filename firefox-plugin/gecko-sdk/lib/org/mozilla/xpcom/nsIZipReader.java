/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIZipReader">
 **/

package org.mozilla.xpcom;

public interface nsIZipReader extends nsISupports
{
  public static final String NS_IZIPREADER_IID =
    "{6ff6a966-9632-11d3-8cd9-0060b0fc14a3}";

  public void init(nsIFile arg1);

  public nsIFile getFile();

  public void open();

  public void close();

  public void test(String arg1);

  public void extract(String arg1, nsIFile arg2);

  public nsIZipEntry getEntry(String arg1);

  public nsISimpleEnumerator findEntries(String arg1);

  public nsIInputStream getInputStream(String arg1);

}
