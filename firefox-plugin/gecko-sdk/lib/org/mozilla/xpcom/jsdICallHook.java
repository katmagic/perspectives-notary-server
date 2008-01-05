/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+jsdICallHook">
 **/

package org.mozilla.xpcom;

public interface jsdICallHook extends nsISupports
{
  public static final String JSDICALLHOOK_IID =
    "{f102caf6-1dd1-11b2-bd43-c1dbacb95a98}";

  public static final long TYPE_TOPLEVEL_START = 0L;

  public static final long TYPE_TOPLEVEL_END = 1L;

  public static final long TYPE_FUNCTION_CALL = 2L;

  public static final long TYPE_FUNCTION_RETURN = 3L;

  public void onCall(jsdIStackFrame arg1, long arg2);

}
