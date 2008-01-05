/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsISchemaLoader">
 **/

package org.mozilla.xpcom;

public interface nsISchemaLoader extends nsISupports
{
  public static final String NS_ISCHEMALOADER_IID =
    "{9b2f0b4a-8f00-4a78-961a-7e84ed49b0b6}";

  public nsISchema load(String arg1);

  public void loadAsync(String arg1, nsISchemaLoadListener arg2);

  public nsISchema processSchemaElement(nsIDOMElement arg1, nsIWebServiceErrorHandler arg2);

}
