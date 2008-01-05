/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIWSDLLoader">
 **/

package org.mozilla.xpcom;

public interface nsIWSDLLoader extends nsISupports
{
  public static final String NS_IWSDLLOADER_IID =
    "{0458dac5-65de-11d5-9b42-00104bdf5339}";

  public nsIWSDLPort load(String arg1, String arg2);

  public void loadAsync(String arg1, String arg2, nsIWSDLLoadListener arg3);

}
