/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+mozITXTToHTMLConv">
 **/

package org.mozilla.xpcom;

public interface mozITXTToHTMLConv extends nsIStreamConverter
{
  public static final String MOZITXTTOHTMLCONV_IID =
    "{77c0e42a-1dd2-11b2-8ebf-edc6606f2f4b}";

  public static final long kEntities = 0L;

  public static final long kURLs = 2L;

  public static final long kGlyphSubstitution = 4L;

  public static final long kStructPhrase = 8L;

  public String scanTXT(String arg1, long arg2);

  public String scanHTML(String arg1, long arg2);

  public long citeLevelTXT(String arg1, long[] arg2);

  public void findURLInPlaintext(String arg1, int arg2, int arg3, int[] arg4, int[] arg5);

}
