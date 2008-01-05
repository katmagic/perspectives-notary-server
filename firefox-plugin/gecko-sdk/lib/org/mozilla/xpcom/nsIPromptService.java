/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIPromptService">
 **/

package org.mozilla.xpcom;

public interface nsIPromptService extends nsISupports
{
  public static final String NS_IPROMPTSERVICE_IID =
    "{1630c61a-325e-49ca-8759-a31b16c47aa5}";

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

  public static final long STD_YES_NO_BUTTONS = 1027L;

  public void alert(nsIDOMWindow arg1, String arg2, String arg3);

  public void alertCheck(nsIDOMWindow arg1, String arg2, String arg3, String arg4, boolean[] arg5);

  public boolean confirm(nsIDOMWindow arg1, String arg2, String arg3);

  public boolean confirmCheck(nsIDOMWindow arg1, String arg2, String arg3, String arg4, boolean[] arg5);

  public int confirmEx(nsIDOMWindow arg1, String arg2, String arg3, long arg4, String arg5, String arg6, String arg7, String arg8, boolean[] arg9);

  public boolean prompt(nsIDOMWindow arg1, String arg2, String arg3, String[] arg4, String arg5, boolean[] arg6);

  public boolean promptUsernameAndPassword(nsIDOMWindow arg1, String arg2, String arg3, String[] arg4, String[] arg5, String arg6, boolean[] arg7);

  public boolean promptPassword(nsIDOMWindow arg1, String arg2, String arg3, String[] arg4, String arg5, boolean[] arg6);

  public boolean select(nsIDOMWindow arg1, String arg2, String arg3, long arg4, String[] arg5, int[] arg6);

}
