/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIDOMCrypto">
 **/

package org.mozilla.xpcom;

public interface nsIDOMCrypto extends nsISupports
{
  public static final String NS_IDOMCRYPTO_IID =
    "{d2b675a5-f05b-4172-bac2-24cc39ffd398}";

  public String getVersion();

  public boolean getEnableSmartCardEvents();

  public void setEnableSmartCardEvents(boolean arg1);

  public nsIDOMCRMFObject generateCRMFRequest();

  public String importUserCertificates(String arg1, String arg2, boolean arg3);

  public String popChallengeResponse(String arg1);

  public String random(int arg1);

  public String signText(String arg1, String arg2);

  public void alert(String arg1);

  public void logout();

  public void disableRightClick();

}
