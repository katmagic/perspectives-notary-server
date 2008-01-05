/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsISyncLoadDOMServi">
 **/

package org.mozilla.xpcom;

public interface nsISyncLoadDOMService extends nsISupports
{
  public static final String NS_ISYNCLOADDOMSERVICE_IID =
    "{96a13c30-695a-492c-918b-04ae3edb4e4c}";

  public nsIDOMDocument loadDocument(nsIChannel arg1, nsIURI arg2);

  public nsIDOMDocument loadDocumentAsXML(nsIChannel arg1, nsIURI arg2);

  public nsIDOMDocument loadLocalDocument(nsIChannel arg1, nsIURI arg2);

  public nsIDOMDocument loadLocalXBLDocument(nsIChannel arg1);

}
