/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsICertificateDialo">
 **/

package org.mozilla.xpcom;

public interface nsICertificateDialogs extends nsISupports
{
  public static final String NS_ICERTIFICATEDIALOGS_IID =
    "{a03ca940-09be-11d5-ac5d-000064657374}";

  public boolean confirmDownloadCACert(nsIInterfaceRequestor arg1, nsIX509Cert arg2, long[] arg3);

  public void notifyCACertExists(nsIInterfaceRequestor arg1);

  public boolean setPKCS12FilePassword(nsIInterfaceRequestor arg1, String arg2);

  public boolean getPKCS12FilePassword(nsIInterfaceRequestor arg1, String arg2);

  public void viewCert(nsIInterfaceRequestor arg1, nsIX509Cert arg2);

  public void crlImportStatusDialog(nsIInterfaceRequestor arg1, nsICRLInfo arg2);

}
