/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIUTF8ConverterSer">
 **/

package org.mozilla.xpcom;

public interface nsIUTF8ConverterService extends nsISupports
{
  public static final String NS_IUTF8CONVERTERSERVICE_IID =
    "{249f52a3-2599-4b00-ba40-0481364831a2}";

  public String convertStringToUTF8(String arg1, String arg2, boolean arg3);

  public String convertURISpecToUTF8(String arg1, String arg2);

}
