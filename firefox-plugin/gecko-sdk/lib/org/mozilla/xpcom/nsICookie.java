/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsICookie">
 **/

package org.mozilla.xpcom;

public interface nsICookie extends nsISupports
{
  public static final String NS_ICOOKIE_IID =
    "{e9fcb9a4-d376-458f-b720-e65e7df593bc}";

  public static final int STATUS_UNKNOWN = 0;

  public static final int STATUS_ACCEPTED = 1;

  public static final int STATUS_DOWNGRADED = 2;

  public static final int STATUS_FLAGGED = 3;

  public static final int STATUS_REJECTED = 4;

  public static final int POLICY_UNKNOWN = 0;

  public static final int POLICY_NONE = 1;

  public static final int POLICY_NO_CONSENT = 2;

  public static final int POLICY_IMPLICIT_CONSENT = 3;

  public static final int POLICY_EXPLICIT_CONSENT = 4;

  public static final int POLICY_NO_II = 5;

  public String getName();

  public String getValue();

  public boolean getIsDomain();

  public String getHost();

  public String getPath();

  public boolean getIsSecure();

  public double getExpires();

  public int getStatus();

  public int getPolicy();

}
