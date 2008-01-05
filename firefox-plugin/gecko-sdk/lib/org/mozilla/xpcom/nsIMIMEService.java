/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIMIMEService">
 **/

package org.mozilla.xpcom;

public interface nsIMIMEService extends nsISupports
{
  public static final String NS_IMIMESERVICE_IID =
    "{5b3675a1-02db-4f8f-a560-b34736635f47}";

  public nsIMIMEInfo getFromTypeAndExtension(String arg1, String arg2);

  public String getTypeFromExtension(String arg1);

  public String getTypeFromURI(nsIURI arg1);

  public String getTypeFromFile(nsIFile arg1);

  public String getPrimaryExtension(String arg1, String arg2);

}
