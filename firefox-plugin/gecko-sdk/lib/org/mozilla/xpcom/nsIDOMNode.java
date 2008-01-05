/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIDOMNode">
 **/

package org.mozilla.xpcom;

public interface nsIDOMNode extends nsISupports
{
  public static final String NS_IDOMNODE_IID =
    "{a6cf907c-15b3-11d2-932e-00805f8add32}";

  public static final int ELEMENT_NODE = 1;

  public static final int ATTRIBUTE_NODE = 2;

  public static final int TEXT_NODE = 3;

  public static final int CDATA_SECTION_NODE = 4;

  public static final int ENTITY_REFERENCE_NODE = 5;

  public static final int ENTITY_NODE = 6;

  public static final int PROCESSING_INSTRUCTION_NODE = 7;

  public static final int COMMENT_NODE = 8;

  public static final int DOCUMENT_NODE = 9;

  public static final int DOCUMENT_TYPE_NODE = 10;

  public static final int DOCUMENT_FRAGMENT_NODE = 11;

  public static final int NOTATION_NODE = 12;

  public String getNodeName();

  public String getNodeValue();

  public void setNodeValue(String arg1);

  public int getNodeType();

  public nsIDOMNode getParentNode();

  public nsIDOMNodeList getChildNodes();

  public nsIDOMNode getFirstChild();

  public nsIDOMNode getLastChild();

  public nsIDOMNode getPreviousSibling();

  public nsIDOMNode getNextSibling();

  public nsIDOMNamedNodeMap getAttributes();

  public nsIDOMDocument getOwnerDocument();

  public nsIDOMNode insertBefore(nsIDOMNode arg1, nsIDOMNode arg2);

  public nsIDOMNode replaceChild(nsIDOMNode arg1, nsIDOMNode arg2);

  public nsIDOMNode removeChild(nsIDOMNode arg1);

  public nsIDOMNode appendChild(nsIDOMNode arg1);

  public boolean hasChildNodes();

  public nsIDOMNode cloneNode(boolean arg1);

  public void normalize();

  public boolean isSupported(String arg1, String arg2);

  public String getNamespaceURI();

  public String getPrefix();

  public void setPrefix(String arg1);

  public String getLocalName();

  public boolean hasAttributes();

}
