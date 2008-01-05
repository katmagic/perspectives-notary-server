/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIX509CertDB">
 **/

package org.mozilla.xpcom;

public interface nsIX509CertDB extends nsISupports
{
  public static final String NS_IX509CERTDB_IID =
    "{da48b3c0-1284-11d5-ac67-000064657374}";

  public static final long UNTRUSTED = 0L;

  public static final long TRUSTED_SSL = 1L;

  public static final long TRUSTED_EMAIL = 2L;

  public static final long TRUSTED_OBJSIGN = 4L;

  public nsIX509Cert findCertByNickname(nsISupports arg1, String arg2);

  public nsIX509Cert findCertByDBKey(String arg1, nsISupports arg2);

  public void findCertNicknames(nsISupports arg1, long arg2, long[] arg3, String[][] arg4);

  public nsIX509Cert findEmailEncryptionCert(String arg1);

  public nsIX509Cert findEmailSigningCert(String arg1);

  public nsIX509Cert findCertByEmailAddress(nsISupports arg1, String arg2);

  public void importCertificates(short[] arg1, long arg2, long arg3, nsIInterfaceRequestor arg4);

  public void importEmailCertificate(short[] arg1, long arg2, nsIInterfaceRequestor arg3);

  public void importServerCertificate(short[] arg1, long arg2, nsIInterfaceRequestor arg3);

  public void importUserCertificate(short[] arg1, long arg2, nsIInterfaceRequestor arg3);

  public void deleteCertificate(nsIX509Cert arg1);

  public void setCertTrust(nsIX509Cert arg1, long arg2, long arg3);

  public boolean isCertTrusted(nsIX509Cert arg1, long arg2, long arg3);

  public void importCertsFromFile(nsISupports arg1, nsILocalFile arg2, long arg3);

  public void importPKCS12File(nsISupports arg1, nsILocalFile arg2);

  public void exportPKCS12File(nsISupports arg1, nsILocalFile arg2, long arg3, nsIX509Cert[] arg4);

  public nsIArray getOCSPResponders();

  public boolean getIsOcspOn();

  public nsIX509Cert constructX509FromBase64(String arg1);

}
