/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIXPCSecurityManag">
 **/

package org.mozilla.xpcom;

public interface nsIXPCSecurityManager extends nsISupports
{
  public static final String NS_IXPCSECURITYMANAGER_IID =
    "{31431440-f1ce-11d2-985a-006008962422}";

  public static final long HOOK_CREATE_WRAPPER = 1L;

  public static final long HOOK_CREATE_INSTANCE = 2L;

  public static final long HOOK_GET_SERVICE = 4L;

  public static final long HOOK_CALL_METHOD = 8L;

  public static final long HOOK_GET_PROPERTY = 16L;

  public static final long HOOK_SET_PROPERTY = 32L;

  public static final long HOOK_ALL = 63L;

  public static final long ACCESS_CALL_METHOD = 0L;

  public static final long ACCESS_GET_PROPERTY = 1L;

  public static final long ACCESS_SET_PROPERTY = 2L;

  public void canCreateWrapper(long arg1, String arg2, nsISupports arg3, nsIClassInfo arg4, long[] arg5);

  public void canCreateInstance(long arg1, String arg2);

  public void canGetService(long arg1, String arg2);

  public void canAccess(long arg1, nsISupports arg2, long arg3, long arg4, nsISupports arg5, nsIClassInfo arg6, long arg7, long[] arg8);

}
