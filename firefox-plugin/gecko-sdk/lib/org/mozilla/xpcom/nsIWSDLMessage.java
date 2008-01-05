/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIWSDLMessage">
 **/

package org.mozilla.xpcom;

public interface nsIWSDLMessage extends nsISupports
{
  public static final String NS_IWSDLMESSAGE_IID =
    "{0458dac3-65de-11d5-9b42-00104bdf5339}";

  public String getName();

  public nsIDOMElement getDocumentation();

  public nsIWSDLBinding getBinding();

  public long getPartCount();

  public nsIWSDLPart getPart(long arg1);

  public nsIWSDLPart getPartByName(String arg1);

}
