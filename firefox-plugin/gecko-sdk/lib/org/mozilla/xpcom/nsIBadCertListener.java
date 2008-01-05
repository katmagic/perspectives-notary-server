/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIBadCertListener">
 **/

package org.mozilla.xpcom;

public interface nsIBadCertListener extends nsISupports
{
  public static final String NS_IBADCERTLISTENER_IID =
    "{86960956-edb0-11d4-998b-00b0d02354a0}";

  public static final short UNINIT_ADD_FLAG = -1;

  public static final short ADD_TRUSTED_FOR_SESSION = 1;

  public static final short ADD_TRUSTED_PERMANENTLY = 2;

  public boolean confirmUnknownIssuer(nsIInterfaceRequestor arg1, nsIX509Cert arg2, short[] arg3);

  public boolean confirmMismatchDomain(nsIInterfaceRequestor arg1, String arg2, nsIX509Cert arg3);

  public boolean confirmCertExpired(nsIInterfaceRequestor arg1, nsIX509Cert arg2);

  public void notifyCrlNextupdate(nsIInterfaceRequestor arg1, String arg2, nsIX509Cert arg3);

}
