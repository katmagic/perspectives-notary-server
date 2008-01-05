/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsICharsetConverter">
 **/

package org.mozilla.xpcom;

public interface nsICharsetConverterManager extends nsISupports
{
  public static final String NS_ICHARSETCONVERTERMANAGER_IID =
    "{f5323a76-c8f7-4c65-8d0c-1250e969c7d5}";

  public nsISupports getUnicodeDecoder(String arg1);

  public nsISupports getUnicodeDecoderRaw(String arg1);

  public nsISupports getUnicodeEncoder(String arg1);

  public nsISupports getUnicodeEncoderRaw(String arg1);

  public String getCharsetAlias(String arg1);

  public nsIUTF8StringEnumerator getDecoderList();

  public nsIUTF8StringEnumerator getEncoderList();

  public nsIUTF8StringEnumerator getCharsetDetectorList();

  public String getCharsetTitle(String arg1);

  public String getCharsetData(String arg1, String arg2);

  public nsIAtom getCharsetLangGroup(String arg1);

  public nsIAtom getCharsetLangGroupRaw(String arg1);

}
