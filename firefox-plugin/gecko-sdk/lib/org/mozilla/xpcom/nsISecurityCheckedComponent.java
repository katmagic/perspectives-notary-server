/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsISecurityCheckedC">
 **/

package org.mozilla.xpcom;

public interface nsISecurityCheckedComponent extends nsISupports
{
  public static final String NS_ISECURITYCHECKEDCOMPONENT_IID =
    "{0dad9e8c-a12d-4dcb-9a6f-7d09839356e1}";

  public String canCreateWrapper(String arg1);

  public String canCallMethod(String arg1, String arg2);

  public String canGetProperty(String arg1, String arg2);

  public String canSetProperty(String arg1, String arg2);

}
