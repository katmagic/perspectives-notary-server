/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIDOMDOMImplementa">
 **/

package org.mozilla.xpcom;

public interface nsIDOMDOMImplementationLS extends nsISupports
{
  public static final String NS_IDOMDOMIMPLEMENTATIONLS_IID =
    "{e2c8b03c-a49a-4923-81b0-ba9a86da0e21}";

  public static final int MODE_SYNCHRONOUS = 1;

  public static final int MODE_ASYNCHRONOUS = 2;

  public nsIDOMLSParser createLSParser(int arg1, String arg2);

  public nsIDOMLSSerializer createLSSerializer();

  public nsIDOMLSInput createLSInput();

  public nsIDOMLSOutput createLSOutput();

}
