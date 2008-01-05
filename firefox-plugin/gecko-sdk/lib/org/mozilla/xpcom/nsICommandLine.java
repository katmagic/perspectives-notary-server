/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsICommandLine">
 **/

package org.mozilla.xpcom;

public interface nsICommandLine extends nsISupports
{
  public static final String NS_ICOMMANDLINE_IID =
    "{bc3173bd-aa46-46a0-9d25-d9867a9659b6}";

  public static final long STATE_INITIAL_LAUNCH = 0L;

  public static final long STATE_REMOTE_AUTO = 1L;

  public static final long STATE_REMOTE_EXPLICIT = 2L;

  public int getLength();

  public String getArgument(int arg1);

  public int findFlag(String arg1, boolean arg2);

  public void removeArguments(int arg1, int arg2);

  public boolean handleFlag(String arg1, boolean arg2);

  public String handleFlagWithParam(String arg1, boolean arg2);

  public long getState();

  public boolean getPreventDefault();

  public void setPreventDefault(boolean arg1);

  public nsIFile getWorkingDirectory();

  public nsIDOMWindow getWindowContext();

  public nsIFile resolveFile(String arg1);

  public nsIURI resolveURI(String arg1);

}
