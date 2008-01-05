/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIX509Cert">
 **/

package org.mozilla.xpcom;

public interface nsIX509Cert extends nsISupports
{
  public static final String NS_IX509CERT_IID =
    "{f0980f60-ee3d-11d4-998b-00b0d02354a0}";

  public static final long UNKNOWN_CERT = 0L;

  public static final long CA_CERT = 1L;

  public static final long USER_CERT = 2L;

  public static final long EMAIL_CERT = 4L;

  public static final long SERVER_CERT = 8L;

  public static final long VERIFIED_OK = 0L;

  public static final long NOT_VERIFIED_UNKNOWN = 1L;

  public static final long CERT_REVOKED = 2L;

  public static final long CERT_EXPIRED = 4L;

  public static final long CERT_NOT_TRUSTED = 8L;

  public static final long ISSUER_NOT_TRUSTED = 16L;

  public static final long ISSUER_UNKNOWN = 32L;

  public static final long INVALID_CA = 64L;

  public static final long USAGE_NOT_ALLOWED = 128L;

  public static final long CERT_USAGE_SSLClient = 0L;

  public static final long CERT_USAGE_SSLServer = 1L;

  public static final long CERT_USAGE_SSLServerWithStepUp = 2L;

  public static final long CERT_USAGE_SSLCA = 3L;

  public static final long CERT_USAGE_EmailSigner = 4L;

  public static final long CERT_USAGE_EmailRecipient = 5L;

  public static final long CERT_USAGE_ObjectSigner = 6L;

  public static final long CERT_USAGE_UserCertImport = 7L;

  public static final long CERT_USAGE_VerifyCA = 8L;

  public static final long CERT_USAGE_ProtectedObjectSigner = 9L;

  public static final long CERT_USAGE_StatusResponder = 10L;

  public static final long CERT_USAGE_AnyCA = 11L;

  public String getNickname();

  public String getEmailAddress();

  public String[] getEmailAddresses(long[] arg1);

  public boolean containsEmailAddress(String arg1);

  public String getSubjectName();

  public String getCommonName();

  public String getOrganization();

  public String getOrganizationalUnit();

  public String getSha1Fingerprint();

  public String getMd5Fingerprint();

  public String getTokenName();

  public String getIssuerName();

  public String getSerialNumber();

  public String getIssuerCommonName();

  public String getIssuerOrganization();

  public String getIssuerOrganizationUnit();

  public nsIX509Cert getIssuer();

  public nsIX509CertValidity getValidity();

  public String getDbKey();

  public String getWindowTitle();

  public nsIArray getChain();

  public void getUsagesArray(boolean arg1, long[] arg2, long[] arg3, String[][] arg4);

  public void getUsagesString(boolean arg1, long[] arg2, String arg3);

  public long verifyForUsage(long arg1);

  public nsIASN1Object getASN1Structure();

  public short[] getRawDER(long[] arg1);

  public boolean equals(nsIX509Cert arg1);

}
