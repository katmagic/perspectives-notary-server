/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIScriptableDateFo">
 **/

package org.mozilla.xpcom;

public interface nsIScriptableDateFormat extends nsISupports
{
  public static final String NS_ISCRIPTABLEDATEFORMAT_IID =
    "{0c89efb0-1aae-11d3-9141-006008a6edf6}";

  public static final int dateFormatNone = 0;

  public static final int dateFormatLong = 1;

  public static final int dateFormatShort = 2;

  public static final int dateFormatYearMonth = 3;

  public static final int dateFormatWeekday = 4;

  public static final int timeFormatNone = 0;

  public static final int timeFormatSeconds = 1;

  public static final int timeFormatNoSeconds = 2;

  public static final int timeFormatSecondsForce24Hour = 3;

  public static final int timeFormatNoSecondsForce24Hour = 4;

  public String formatDateTime(String arg1, int arg2, int arg3, int arg4, int arg5, int arg6, int arg7, int arg8, int arg9);

  public String formatDate(String arg1, int arg2, int arg3, int arg4, int arg5);

  public String formatTime(String arg1, int arg2, int arg3, int arg4, int arg5);

}
