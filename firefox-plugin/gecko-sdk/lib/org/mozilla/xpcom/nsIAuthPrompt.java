/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIAuthPrompt">
 **/

package org.mozilla.xpcom;

public interface nsIAuthPrompt extends nsISupports
{
  public static final String NS_IAUTHPROMPT_IID =
    "{2f977d45-5485-11d4-87e2-0010a4e75ef2}";

  public static final long SAVE_PASSWORD_NEVER = 0L;

  public static final long SAVE_PASSWORD_FOR_SESSION = 1L;

  public static final long SAVE_PASSWORD_PERMANENTLY = 2L;

  public boolean prompt(String arg1, String arg2, String arg3, long arg4, String arg5, String[] arg6);

  public boolean promptUsernameAndPassword(String arg1, String arg2, String arg3, long arg4, String[] arg5, String[] arg6);

  public boolean promptPassword(String arg1, String arg2, String arg3, long arg4, String[] arg5);

}
