/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIXPInstallManager">
 **/

package org.mozilla.xpcom;

public interface nsIXPInstallManager extends nsISupports
{
  public static final String NS_IXPINSTALLMANAGER_IID =
    "{566689cb-9926-4bec-a66e-a034e364ad2c}";

  public void initManagerFromChrome(String[] arg1, long arg2, nsIXPIProgressDialog arg3);

  public void initManagerWithHashes(String[] arg1, String[] arg2, long arg3, nsIXPIProgressDialog arg4);

}
