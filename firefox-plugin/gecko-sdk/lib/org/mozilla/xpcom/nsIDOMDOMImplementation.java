/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIDOMDOMImplementa">
 **/

package org.mozilla.xpcom;

public interface nsIDOMDOMImplementation extends nsISupports
{
  public static final String NS_IDOMDOMIMPLEMENTATION_IID =
    "{a6cf9074-15b3-11d2-932e-00805f8add32}";

  public boolean hasFeature(String arg1, String arg2);

  public nsIDOMDocumentType createDocumentType(String arg1, String arg2, String arg3);

  public nsIDOMDocument createDocument(String arg1, String arg2, nsIDOMDocumentType arg3);

}
