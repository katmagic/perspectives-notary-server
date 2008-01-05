/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIDOM3Document">
 **/

package org.mozilla.xpcom;

public interface nsIDOM3Document extends nsIDOM3Node
{
  public static final String NS_IDOM3DOCUMENT_IID =
    "{2e0e9ea1-72ab-4d9e-bdeb-ca64e1abeba4}";

  public String getInputEncoding();

  public String getXmlEncoding();

  public boolean getXmlStandalone();

  public void setXmlStandalone(boolean arg1);

  public String getXmlVersion();

  public void setXmlVersion(String arg1);

  public boolean getStrictErrorChecking();

  public void setStrictErrorChecking(boolean arg1);

  public String getDocumentURI();

  public void setDocumentURI(String arg1);

  public nsIDOMNode adoptNode(nsIDOMNode arg1);

  public nsIDOMDOMConfiguration getDomConfig();

  public void normalizeDocument();

  public nsIDOMNode renameNode(nsIDOMNode arg1, String arg2, String arg3);

}
