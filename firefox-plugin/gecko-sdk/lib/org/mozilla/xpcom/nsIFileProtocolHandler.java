/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIFileProtocolHand">
 **/

package org.mozilla.xpcom;

public interface nsIFileProtocolHandler extends nsIProtocolHandler
{
  public static final String NS_IFILEPROTOCOLHANDLER_IID =
    "{255602ea-c31f-4d29-8f35-905ead3f76f4}";

  public nsIURI newFileURI(nsIFile arg1);

  public String getURLSpecFromFile(nsIFile arg1);

  public nsIFile getFileFromURLSpec(String arg1);

  public nsIURI readURLFile(nsIFile arg1);

}
