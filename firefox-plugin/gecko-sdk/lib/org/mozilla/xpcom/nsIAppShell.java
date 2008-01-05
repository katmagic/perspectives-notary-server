/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIAppShell">
 **/

package org.mozilla.xpcom;

public interface nsIAppShell extends nsISupports
{
  public static final String NS_IAPPSHELL_IID =
    "{a0757c31-eeac-11d1-9ec1-00aa002fb821}";

  public void create(long[] arg1, String[] arg2);

  public void run();

  public void spinup();

  public void spindown();

  public void listenToEventQueue(long arg1, boolean arg2);

  public void getNativeEvent(long arg1, long arg2);

  public void dispatchNativeEvent(boolean arg1, long arg2);

  public void exit();

}
