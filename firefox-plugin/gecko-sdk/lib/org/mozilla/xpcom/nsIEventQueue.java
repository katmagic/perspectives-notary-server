/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIEventQueue">
 **/

package org.mozilla.xpcom;

public interface nsIEventQueue extends nsIEventTarget
{
  public static final String NS_IEVENTQUEUE_IID =
    "{176afb41-00a4-11d3-9f2a-00400553eef0}";

  public boolean pendingEvents();

  public void processPendingEvents();

  public void eventLoop();

  public void init(boolean arg1);

  public void enterMonitor();

  public void exitMonitor();

  public boolean isQueueNative();

  public void stopAcceptingEvents();

}
