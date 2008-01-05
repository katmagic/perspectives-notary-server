/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsPIXPIProxy">
 **/

package org.mozilla.xpcom;

public interface nsPIXPIProxy extends nsISupports
{
  public static final String NS_PIXPIPROXY_IID =
    "{6f9d2890-167d-11d5-8daf-000064657374}";

  public void refreshPlugins(boolean arg1);

  public void notifyRestartNeeded();

  public void alert(String arg1, String arg2);

  public int confirmEx(String arg1, String arg2, long arg3, String arg4, String arg5, String arg6, String arg7, boolean[] arg8);

}
