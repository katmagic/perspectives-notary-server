/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIXULAppInfo">
 **/

package org.mozilla.xpcom;

public interface nsIXULAppInfo extends nsISupports
{
  public static final String NS_IXULAPPINFO_IID =
    "{a61ede2a-ef09-11d9-a5ce-001124787b2e}";

  public String getVendor();

  public String getName();

  public String getID();

  public String getVersion();

  public String getAppBuildID();

  public String getPlatformVersion();

  public String getPlatformBuildID();

}
