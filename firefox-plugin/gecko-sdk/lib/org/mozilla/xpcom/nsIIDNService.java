/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIIDNService">
 **/

package org.mozilla.xpcom;

public interface nsIIDNService extends nsISupports
{
  public static final String NS_IIDNSERVICE_IID =
    "{7b67747e-a8c4-4832-80c7-39ebb0c11f94}";

  public String convertUTF8toACE(String arg1);

  public String convertACEtoUTF8(String arg1);

  public boolean isACE(String arg1);

  public String normalize(String arg1);

}
