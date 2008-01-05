/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIExternalHelperAp">
 **/

package org.mozilla.xpcom;

public interface nsIExternalHelperAppService extends nsISupports
{
  public static final String NS_IEXTERNALHELPERAPPSERVICE_IID =
    "{0ea90cf3-2dd9-470f-8f76-f141743c5678}";

  public nsIStreamListener doContent(String arg1, nsIRequest arg2, nsIInterfaceRequestor arg3);

  public boolean applyDecodingForExtension(String arg1, String arg2);

}
