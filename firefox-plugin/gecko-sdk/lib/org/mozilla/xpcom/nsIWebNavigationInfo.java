/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIWebNavigationInf">
 **/

package org.mozilla.xpcom;

public interface nsIWebNavigationInfo extends nsISupports
{
  public static final String NS_IWEBNAVIGATIONINFO_IID =
    "{62a93afb-93a1-465c-84c8-0432264229de}";

  public static final long UNSUPPORTED = 0L;

  public static final long IMAGE = 1L;

  public static final long PLUGIN = 2L;

  public static final long OTHER = 32768L;

  public long isTypeSupported(String arg1, nsIWebNavigation arg2);

}
