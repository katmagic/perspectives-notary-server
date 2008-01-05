/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIDOMLSException">
 **/

package org.mozilla.xpcom;

public interface nsIDOMLSException extends nsISupports
{
  public static final String NS_IDOMLSEXCEPTION_IID =
    "{1cc8e4b3-1dbb-4adc-a913-1527bf67748c}";

  public static final int PARSE_ERR = 81;

  public static final int SERIALIZE_ERR = 82;

  public int getCode();

}
