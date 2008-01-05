/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIDOMDocumentXBL">
 **/

package org.mozilla.xpcom;

public interface nsIDOMDocumentXBL extends nsISupports
{
  public static final String NS_IDOMDOCUMENTXBL_IID =
    "{c7c0ae9b-a0ba-4f4e-9f2c-c18deb62ee8b}";

  public nsIDOMNodeList getAnonymousNodes(nsIDOMElement arg1);

  public nsIDOMElement getAnonymousElementByAttribute(nsIDOMElement arg1, String arg2, String arg3);

  public void addBinding(nsIDOMElement arg1, String arg2);

  public void removeBinding(nsIDOMElement arg1, String arg2);

  public nsIDOMElement getBindingParent(nsIDOMNode arg1);

  public nsIDOMDocument loadBindingDocument(String arg1);

}
