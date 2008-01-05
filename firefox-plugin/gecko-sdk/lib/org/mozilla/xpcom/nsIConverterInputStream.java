/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIConverterInputSt">
 **/

package org.mozilla.xpcom;

public interface nsIConverterInputStream extends nsIUnicharInputStream
{
  public static final String NS_ICONVERTERINPUTSTREAM_IID =
    "{fc66ffb6-5404-4908-a4a3-27f92fa0579d}";

  public static final int DEFAULT_REPLACEMENT_CHARACTER = 65533;

  public void init(nsIInputStream arg1, String arg2, int arg3, int arg4);

}
