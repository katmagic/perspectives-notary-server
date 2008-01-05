/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIStreamConverterS">
 **/

package org.mozilla.xpcom;

public interface nsIStreamConverterService extends nsISupports
{
  public static final String NS_ISTREAMCONVERTERSERVICE_IID =
    "{e086e1e2-40ff-4193-8b8c-bd548babe70d}";

  public nsIInputStream convert(nsIInputStream arg1, String arg2, String arg3, nsISupports arg4);

  public nsIStreamListener asyncConvertData(String arg1, String arg2, nsIStreamListener arg3, nsISupports arg4);

}
