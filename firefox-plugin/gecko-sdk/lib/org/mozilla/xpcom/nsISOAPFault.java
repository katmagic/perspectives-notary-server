/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsISOAPFault">
 **/

package org.mozilla.xpcom;

public interface nsISOAPFault extends nsISupports
{
  public static final String NS_ISOAPFAULT_IID =
    "{99ec6694-535f-11d4-9a58-000064657374}";

  public nsIDOMElement getElement();

  public void setElement(nsIDOMElement arg1);

  public String getFaultNamespaceURI();

  public String getFaultCode();

  public String getFaultString();

  public String getFaultActor();

  public nsIDOMElement getDetail();

}
