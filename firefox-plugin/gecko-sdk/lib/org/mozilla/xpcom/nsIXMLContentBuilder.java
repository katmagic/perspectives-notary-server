/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIXMLContentBuilde">
 **/

package org.mozilla.xpcom;

public interface nsIXMLContentBuilder extends nsISupports
{
  public static final String NS_IXMLCONTENTBUILDER_IID =
    "{e9c4cd4f-cd41-43d0-bf3b-48abb9cde90f}";

  public void clear(nsIDOMElement arg1);

  public void setDocument(nsIDOMDocument arg1);

  public void setElementNamespace(String arg1);

  public void beginElement(String arg1);

  public void endElement();

  public void attrib(String arg1, String arg2);

  public void textNode(String arg1);

  public nsIDOMElement getRoot();

  public nsIDOMElement getCurrent();

}
