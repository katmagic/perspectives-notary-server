/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIScriptError">
 **/

package org.mozilla.xpcom;

public interface nsIScriptError extends nsIConsoleMessage
{
  public static final String NS_ISCRIPTERROR_IID =
    "{b0196fc7-1913-441a-882a-453c0d8b89b8}";

  public static final long errorFlag = 0L;

  public static final long warningFlag = 1L;

  public static final long exceptionFlag = 2L;

  public static final long strictFlag = 4L;

  public String getErrorMessage();

  public String getSourceName();

  public String getSourceLine();

  public long getLineNumber();

  public long getColumnNumber();

  public long getFlags();

  public String getCategory();

  public void init(String arg1, String arg2, String arg3, long arg4, long arg5, long arg6, String arg7);

  public String toString();

}
