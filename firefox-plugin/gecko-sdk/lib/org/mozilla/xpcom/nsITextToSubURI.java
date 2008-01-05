/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsITextToSubURI">
 **/

package org.mozilla.xpcom;

public interface nsITextToSubURI extends nsISupports
{
  public static final String NS_ITEXTTOSUBURI_IID =
    "{8b042e24-6f87-11d3-b3c8-00805f8a6670}";

  public String convertAndEscape(String arg1, String arg2);

  public String unEscapeAndConvert(String arg1, String arg2);

  public String unEscapeURIForUI(String arg1, String arg2);

  public String unEscapeNonAsciiURI(String arg1, String arg2);

}
