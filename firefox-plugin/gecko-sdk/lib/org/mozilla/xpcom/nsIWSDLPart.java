/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIWSDLPart">
 **/

package org.mozilla.xpcom;

public interface nsIWSDLPart extends nsISupports
{
  public static final String NS_IWSDLPART_IID =
    "{0458dac4-65de-11d5-9b42-00104bdf5339}";

  public String getName();

  public nsIWSDLBinding getBinding();

  public String getType();

  public String getElementName();

  public nsISchemaComponent getSchemaComponent();

}
