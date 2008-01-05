/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIDOMDocument">
 **/

package org.mozilla.xpcom;

public interface nsIDOMDocument extends nsIDOMNode
{
  public static final String NS_IDOMDOCUMENT_IID =
    "{a6cf9075-15b3-11d2-932e-00805f8add32}";

  public nsIDOMDocumentType getDoctype();

  public nsIDOMDOMImplementation getImplementation();

  public nsIDOMElement getDocumentElement();

  public nsIDOMElement createElement(String arg1);

  public nsIDOMDocumentFragment createDocumentFragment();

  public nsIDOMText createTextNode(String arg1);

  public nsIDOMComment createComment(String arg1);

  public nsIDOMCDATASection createCDATASection(String arg1);

  public nsIDOMProcessingInstruction createProcessingInstruction(String arg1, String arg2);

  public nsIDOMAttr createAttribute(String arg1);

  public nsIDOMEntityReference createEntityReference(String arg1);

  public nsIDOMNodeList getElementsByTagName(String arg1);

  public nsIDOMNode importNode(nsIDOMNode arg1, boolean arg2);

  public nsIDOMElement createElementNS(String arg1, String arg2);

  public nsIDOMAttr createAttributeNS(String arg1, String arg2);

  public nsIDOMNodeList getElementsByTagNameNS(String arg1, String arg2);

  public nsIDOMElement getElementById(String arg1);

}
