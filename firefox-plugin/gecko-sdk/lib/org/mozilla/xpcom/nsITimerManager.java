/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsITimerManager">
 **/

package org.mozilla.xpcom;

public interface nsITimerManager extends nsISupports
{
  public static final String NS_ITIMERMANAGER_IID =
    "{8fce8c6a-1dd2-11b2-8352-8cdd2b965efc}";

  public boolean getUseIdleTimers();

  public void setUseIdleTimers(boolean arg1);

  public boolean hasIdleTimers();

  public void fireNextIdleTimer();

}
