/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIExternalProtocol">
 **/

package org.mozilla.xpcom;

public interface nsIExternalProtocolService extends nsISupports
{
  public static final String NS_IEXTERNALPROTOCOLSERVICE_IID =
    "{a49813a4-98b7-4bdb-998c-8bd9704af0c0}";

  public boolean externalProtocolHandlerExists(String arg1);

  public boolean isExposedProtocol(String arg1);

  public void loadUrl(nsIURI arg1);

  public void loadURI(nsIURI arg1, nsIPrompt arg2);

  public String getApplicationDescription(String arg1);

}
