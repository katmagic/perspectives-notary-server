/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIDOMDocumentType">
 **/

package org.mozilla.xpcom;

public interface nsIDOMDocumentType extends nsIDOMNode
{
  public static final String NS_IDOMDOCUMENTTYPE_IID =
    "{a6cf9077-15b3-11d2-932e-00805f8add32}";

  public String getName();

  public nsIDOMNamedNodeMap getEntities();

  public nsIDOMNamedNodeMap getNotations();

  public String getPublicId();

  public String getSystemId();

  public String getInternalSubset();

}
