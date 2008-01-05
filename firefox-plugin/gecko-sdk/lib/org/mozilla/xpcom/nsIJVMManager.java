/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIJVMManager">
 **/

package org.mozilla.xpcom;

public interface nsIJVMManager extends nsISupports
{
  public static final String NS_IJVMMANAGER_IID =
    "{a1e5ed50-aa4a-11d1-85b2-00805f0e4dfe}";

  public void showJavaConsole();

  public boolean isAllPermissionGranted(String arg1, String arg2, String arg3, String arg4);

  public nsISupports isAppletTrusted(String arg1, long arg2, String arg3, long arg4, boolean[] arg5);

  public boolean getJavaEnabled();

}
