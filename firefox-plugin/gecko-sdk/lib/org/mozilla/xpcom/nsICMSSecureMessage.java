/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsICMSSecureMessage">
 **/

package org.mozilla.xpcom;

public interface nsICMSSecureMessage extends nsISupports
{
  public static final String NS_ICMSSECUREMESSAGE_IID =
    "{14b4394a-1dd2-11b2-b4fd-ba4a194fe97e}";

  public String getCertByPrefID(String arg1);

  public nsIX509Cert decodeCert(String arg1);

  public String sendMessage(String arg1, String arg2);

  public String receiveMessage(String arg1);

}
