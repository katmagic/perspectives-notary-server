/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIWSDLPort">
 **/

package org.mozilla.xpcom;

public interface nsIWSDLPort extends nsISupports
{
  public static final String NS_IWSDLPORT_IID =
    "{0458dac1-65de-11d5-9b42-00104bdf5339}";

  public String getName();

  public nsIDOMElement getDocumentation();

  public nsIWSDLBinding getBinding();

  public long getOperationCount();

  public nsIWSDLOperation getOperation(long arg1);

  public nsIWSDLOperation getOperationByName(String arg1);

}
