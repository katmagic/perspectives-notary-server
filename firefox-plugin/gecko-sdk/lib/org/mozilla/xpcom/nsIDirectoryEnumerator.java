/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIDirectoryEnumera">
 **/

package org.mozilla.xpcom;

public interface nsIDirectoryEnumerator extends nsISupports
{
  public static final String NS_IDIRECTORYENUMERATOR_IID =
    "{31f7f4ae-6916-4f2d-a81e-926a4e3022ee}";

  public nsIFile getNextFile();

  public void close();

}
