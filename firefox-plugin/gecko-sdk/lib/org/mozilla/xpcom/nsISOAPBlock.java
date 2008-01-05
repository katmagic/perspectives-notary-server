/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsISOAPBlock">
 **/

package org.mozilla.xpcom;

public interface nsISOAPBlock extends nsISupports
{
  public static final String NS_ISOAPBLOCK_IID =
    "{843afaa8-1dd2-11b2-8b0d-9b5d16fe64ea}";

  public void init(nsISOAPAttachments arg1, int arg2);

  public String getNamespaceURI();

  public void setNamespaceURI(String arg1);

  public String getName();

  public void setName(String arg1);

  public nsISOAPEncoding getEncoding();

  public void setEncoding(nsISOAPEncoding arg1);

  public nsISchemaType getSchemaType();

  public void setSchemaType(nsISchemaType arg1);

  public nsIDOMElement getElement();

  public void setElement(nsIDOMElement arg1);

  public nsIVariant getValue();

  public void setValue(nsIVariant arg1);

}
