/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsISecretDecoderRin">
 **/

package org.mozilla.xpcom;

public interface nsISecretDecoderRing extends nsISupports
{
  public static final String NS_ISECRETDECODERRING_IID =
    "{0ec80360-075c-11d4-9fd4-00c04f1b83d8}";

  public String encryptString(String arg1);

  public String decryptString(String arg1);

  public void changePassword();

  public void logout();

  public void logoutAndTeardown();

}
