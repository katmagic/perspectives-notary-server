/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIUserCertPicker">
 **/

package org.mozilla.xpcom;

public interface nsIUserCertPicker extends nsISupports
{
  public static final String NS_IUSERCERTPICKER_IID =
    "{06d018e0-d41b-4629-a4fc-daaa6029888e}";

  public nsIX509Cert pickByUsage(nsIInterfaceRequestor arg1, String arg2, int arg3, boolean arg4, boolean arg5, boolean[] arg6);

}
