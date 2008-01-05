/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsISecurityWarningD">
 **/

package org.mozilla.xpcom;

public interface nsISecurityWarningDialogs extends nsISupports
{
  public static final String NS_ISECURITYWARNINGDIALOGS_IID =
    "{1c399d06-1dd2-11b2-bc58-c87cbcacdb78}";

  public boolean confirmEnteringSecure(nsIInterfaceRequestor arg1);

  public boolean confirmEnteringWeak(nsIInterfaceRequestor arg1);

  public boolean confirmLeavingSecure(nsIInterfaceRequestor arg1);

  public boolean confirmMixedMode(nsIInterfaceRequestor arg1);

  public boolean confirmPostToInsecure(nsIInterfaceRequestor arg1);

  public boolean confirmPostToInsecureFromSecure(nsIInterfaceRequestor arg1);

}
