/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIHttpAuthManager">
 **/

package org.mozilla.xpcom;

public interface nsIHttpAuthManager extends nsISupports
{
  public static final String NS_IHTTPAUTHMANAGER_IID =
    "{7ce8e9d1-8b4b-4883-a307-66fe12a50153}";

  public void getAuthIdentity(String arg1, String arg2, int arg3, String arg4, String arg5, String arg6, String arg7, String arg8, String arg9);

  public void setAuthIdentity(String arg1, String arg2, int arg3, String arg4, String arg5, String arg6, String arg7, String arg8, String arg9);

  public void clearAll();

}
