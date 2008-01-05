/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsISOAPPortBinding">
 **/

package org.mozilla.xpcom;

public interface nsISOAPPortBinding extends nsIWSDLSOAPBinding
{
  public static final String NS_ISOAPPORTBINDING_IID =
    "{0458dac7-65de-11d5-9b42-00104bdf5339}";

  public static final int SOAP_VERSION_1_1 = 0;

  public static final int SOAP_VERSION_1_2 = 1;

  public static final int SOAP_VERSION_UNKNOWN = 32767;

  public String getName();

  public String getAddress();

  public int getStyle();

  public String getTransport();

  public int getSoapVersion();

}
