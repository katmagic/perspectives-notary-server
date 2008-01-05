/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIFontEnumerator">
 **/

package org.mozilla.xpcom;

public interface nsIFontEnumerator extends nsISupports
{
  public static final String NS_IFONTENUMERATOR_IID =
    "{a6cf9114-15b3-11d2-932e-00805f8add32}";

  public String[] enumerateAllFonts(long[] arg1);

  public String[] enumerateFonts(String arg1, String arg2, long[] arg3);

  public boolean haveFontFor(String arg1);

  public String getDefaultFont(String arg1, String arg2);

  public boolean updateFontList();

}
