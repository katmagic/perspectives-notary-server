/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIScriptableUnicod">
 **/

package org.mozilla.xpcom;

public interface nsIScriptableUnicodeConverter extends nsISupports
{
  public static final String NS_ISCRIPTABLEUNICODECONVERTER_IID =
    "{1ea19c6c-c59f-4fd7-9fc7-151e946baca0}";

  public String convertFromUnicode(String arg1);

  public String finish();

  public String convertToUnicode(String arg1);

  public String convertFromByteArray(short[] arg1, long arg2);

  public short[] convertToByteArray(String arg1, long[] arg2);

  public nsIInputStream convertToInputStream(String arg1);

  public String getCharset();

  public void setCharset(String arg1);

}
