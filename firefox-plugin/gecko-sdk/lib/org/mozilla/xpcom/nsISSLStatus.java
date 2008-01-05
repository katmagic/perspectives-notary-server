/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsISSLStatus">
 **/

package org.mozilla.xpcom;

public interface nsISSLStatus extends nsISupports
{
  public static final String NS_ISSLSTATUS_IID =
    "{7b2ca1ca-1dd2-11b2-87ec-d217dbe22b85}";

  public nsIX509Cert getServerCert();

  public String getCipherName();

  public long getKeyLength();

  public long getSecretKeyLength();

}
