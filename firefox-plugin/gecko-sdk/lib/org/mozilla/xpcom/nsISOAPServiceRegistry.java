/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsISOAPServiceRegis">
 **/

package org.mozilla.xpcom;

public interface nsISOAPServiceRegistry
{
  public static final String NS_ISOAPSERVICEREGISTRY_IID =
    "{9790d6bc-1dd1-11b2-afe0-bcb310c078bf}";

  public boolean addConfiguration(nsIDOMElement arg1);

  public void addSource(String arg1, boolean arg2);

  public void addService(nsISOAPService arg1);

  public nsISOAPEncodingRegistry getEncodings();

  public void setEncodings(nsISOAPEncodingRegistry arg1);

}
