/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIDOMElement">
 **/

package org.mozilla.xpcom;

public interface nsIDOMElement extends nsIDOMNode
{
  public static final String NS_IDOMELEMENT_IID =
    "{a6cf9078-15b3-11d2-932e-00805f8add32}";

  public String getTagName();

  public String getAttribute(String arg1);

  public void setAttribute(String arg1, String arg2);

  public void removeAttribute(String arg1);

  public nsIDOMAttr getAttributeNode(String arg1);

  public nsIDOMAttr setAttributeNode(nsIDOMAttr arg1);

  public nsIDOMAttr removeAttributeNode(nsIDOMAttr arg1);

  public nsIDOMNodeList getElementsByTagName(String arg1);

  public String getAttributeNS(String arg1, String arg2);

  public void setAttributeNS(String arg1, String arg2, String arg3);

  public void removeAttributeNS(String arg1, String arg2);

  public nsIDOMAttr getAttributeNodeNS(String arg1, String arg2);

  public nsIDOMAttr setAttributeNodeNS(nsIDOMAttr arg1);

  public nsIDOMNodeList getElementsByTagNameNS(String arg1, String arg2);

  public boolean hasAttribute(String arg1);

  public boolean hasAttributeNS(String arg1, String arg2);

}
