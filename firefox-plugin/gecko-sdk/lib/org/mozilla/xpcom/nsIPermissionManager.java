/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIPermissionManage">
 **/

package org.mozilla.xpcom;

public interface nsIPermissionManager extends nsISupports
{
  public static final String NS_IPERMISSIONMANAGER_IID =
    "{4f6b5e00-0c36-11d5-a535-0010a401eb10}";

  public static final long UNKNOWN_ACTION = 0L;

  public static final long ALLOW_ACTION = 1L;

  public static final long DENY_ACTION = 2L;

  public void add(nsIURI arg1, String arg2, long arg3);

  public void remove(String arg1, String arg2);

  public void removeAll();

  public long testPermission(nsIURI arg1, String arg2);

  public nsISimpleEnumerator getEnumerator();

}
