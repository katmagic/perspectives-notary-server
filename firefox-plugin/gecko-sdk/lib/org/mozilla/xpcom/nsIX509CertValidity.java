/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIX509CertValidity">
 **/

package org.mozilla.xpcom;

public interface nsIX509CertValidity extends nsISupports
{
  public static final String NS_IX509CERTVALIDITY_IID =
    "{e701dfd8-1dd1-11b2-a172-ffa6cc6156ad}";

  public double getNotBefore();

  public String getNotBeforeLocalTime();

  public String getNotBeforeLocalDay();

  public String getNotBeforeGMT();

  public double getNotAfter();

  public String getNotAfterLocalTime();

  public String getNotAfterLocalDay();

  public String getNotAfterGMT();

}
