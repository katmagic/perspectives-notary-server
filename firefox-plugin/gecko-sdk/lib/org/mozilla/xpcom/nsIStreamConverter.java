/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIStreamConverter">
 **/

package org.mozilla.xpcom;

public interface nsIStreamConverter extends nsIStreamListener
{
  public static final String NS_ISTREAMCONVERTER_IID =
    "{0b6e2c69-5cf5-48b0-9dfd-c95950e2cc7b}";

  public nsIInputStream convert(nsIInputStream arg1, String arg2, String arg3, nsISupports arg4);

  public void asyncConvertData(String arg1, String arg2, nsIStreamListener arg3, nsISupports arg4);

}
