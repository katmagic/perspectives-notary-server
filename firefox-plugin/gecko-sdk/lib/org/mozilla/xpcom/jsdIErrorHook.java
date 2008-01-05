/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+jsdIErrorHook">
 **/

package org.mozilla.xpcom;

public interface jsdIErrorHook extends nsISupports
{
  public static final String JSDIERRORHOOK_IID =
    "{b7dd3c1c-1dd1-11b2-83eb-8a857d199e0f}";

  public static final long REPORT_ERROR = 0L;

  public static final long REPORT_WARNING = 1L;

  public static final long REPORT_EXCEPTION = 2L;

  public static final long REPORT_STRICT = 4L;

  public boolean onError(String arg1, String arg2, long arg3, long arg4, long arg5, long arg6, jsdIValue arg7);

}
