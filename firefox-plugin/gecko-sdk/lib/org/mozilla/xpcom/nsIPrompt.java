/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIPrompt">
 **/

package org.mozilla.xpcom;

public interface nsIPrompt extends nsISupports
{
  public static final String NS_IPROMPT_IID =
    "{a63f70c0-148b-11d3-9333-00104ba0fd40}";

  public static final long BUTTON_POS_0 = 1L;

  public static final long BUTTON_POS_1 = 256L;

  public static final long BUTTON_POS_2 = 65536L;

  public static final long BUTTON_TITLE_OK = 1L;

  public static final long BUTTON_TITLE_CANCEL = 2L;

  public static final long BUTTON_TITLE_YES = 3L;

  public static final long BUTTON_TITLE_NO = 4L;

  public static final long BUTTON_TITLE_SAVE = 5L;

  public static final long BUTTON_TITLE_DONT_SAVE = 6L;

  public static final long BUTTON_TITLE_REVERT = 7L;

  public static final long BUTTON_TITLE_IS_STRING = 127L;

  public static final long BUTTON_POS_0_DEFAULT = 0L;

  public static final long BUTTON_POS_1_DEFAULT = 16777216L;

  public static final long BUTTON_POS_2_DEFAULT = 33554432L;

  public static final long BUTTON_DELAY_ENABLE = 67108864L;

  public static final long STD_OK_CANCEL_BUTTONS = 513L;

  public void alert(String arg1, String arg2);

  public void alertCheck(String arg1, String arg2, String arg3, boolean[] arg4);

  public boolean confirm(String arg1, String arg2);

  public boolean confirmCheck(String arg1, String arg2, String arg3, boolean[] arg4);

  public int confirmEx(String arg1, String arg2, long arg3, String arg4, String arg5, String arg6, String arg7, boolean[] arg8);

  public boolean prompt(String arg1, String arg2, String[] arg3, String arg4, boolean[] arg5);

  public boolean promptPassword(String arg1, String arg2, String[] arg3, String arg4, boolean[] arg5);

  public boolean promptUsernameAndPassword(String arg1, String arg2, String[] arg3, String[] arg4, String arg5, boolean[] arg6);

  public boolean select(String arg1, String arg2, long arg3, String[] arg4, int[] arg5);

}
