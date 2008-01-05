/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIWSDLOperation">
 **/

package org.mozilla.xpcom;

public interface nsIWSDLOperation extends nsISupports
{
  public static final String NS_IWSDLOPERATION_IID =
    "{0458dac2-65de-11d5-9b42-00104bdf5339}";

  public String getName();

  public nsIDOMElement getDocumentation();

  public nsIWSDLBinding getBinding();

  public nsIWSDLMessage getInput();

  public nsIWSDLMessage getOutput();

  public long getFaultCount();

  public nsIWSDLMessage getFault(long arg1);

  public long getParameterOrderCount();

  public String getParameter(long arg1);

  public long getParameterIndex(String arg1);

}
