/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIRDFXMLParser">
 **/

package org.mozilla.xpcom;

public interface nsIRDFXMLParser extends nsISupports
{
  public static final String NS_IRDFXMLPARSER_IID =
    "{1831dd2e-1dd2-11b2-bdb3-86b7b50b70b5}";

  public nsIStreamListener parseAsync(nsIRDFDataSource arg1, nsIURI arg2);

  public void parseString(nsIRDFDataSource arg1, nsIURI arg2, String arg3);

}
