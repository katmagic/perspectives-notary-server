/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIDOM3Node">
 **/

package org.mozilla.xpcom;

public interface nsIDOM3Node extends nsISupports
{
  public static final String NS_IDOM3NODE_IID =
    "{29fb2a18-1dd2-11b2-8dd9-a6fd5d5ad12f}";

  public static final int DOCUMENT_POSITION_DISCONNECTED = 1;

  public static final int DOCUMENT_POSITION_PRECEDING = 2;

  public static final int DOCUMENT_POSITION_FOLLOWING = 4;

  public static final int DOCUMENT_POSITION_CONTAINS = 8;

  public static final int DOCUMENT_POSITION_CONTAINED_BY = 16;

  public static final int DOCUMENT_POSITION_IMPLEMENTATION_SPECIFIC = 32;

  public String getBaseURI();

  public int compareDocumentPosition(nsIDOMNode arg1);

  public String getTextContent();

  public void setTextContent(String arg1);

  public boolean isSameNode(nsIDOMNode arg1);

  public String lookupPrefix(String arg1);

  public boolean isDefaultNamespace(String arg1);

  public String lookupNamespaceURI(String arg1);

  public boolean isEqualNode(nsIDOMNode arg1);

  public nsISupports getFeature(String arg1, String arg2);

  public nsIVariant setUserData(String arg1, nsIVariant arg2, nsIDOMUserDataHandler arg3);

  public nsIVariant getUserData(String arg1);

}
