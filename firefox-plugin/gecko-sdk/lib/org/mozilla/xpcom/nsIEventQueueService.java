/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIEventQueueServic">
 **/

package org.mozilla.xpcom;

public interface nsIEventQueueService extends nsISupports
{
  public static final String NS_IEVENTQUEUESERVICE_IID =
    "{a6cf90dc-15b3-11d2-932e-00805f8add32}";

  public static final int CURRENT_THREAD_EVENT_QUEUE = 0;

  public static final int UI_THREAD_EVENT_QUEUE = 1;

  public void createThreadEventQueue();

  public void createMonitoredThreadEventQueue();

  public void destroyThreadEventQueue();

  public nsIEventQueue createFromIThread(nsIThread arg1, boolean arg2);

  public nsIEventQueue pushThreadEventQueue();

  public void popThreadEventQueue(nsIEventQueue arg1);

  public nsIEventQueue getSpecialEventQueue(int arg1);

}
