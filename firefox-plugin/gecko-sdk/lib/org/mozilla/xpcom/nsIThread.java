/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIThread">
 **/

package org.mozilla.xpcom;

public interface nsIThread extends nsISupports
{
  public static final String NS_ITHREAD_IID =
    "{6be5e380-6886-11d3-9382-00104ba0fd40}";

  public static final long PRIORITY_LOW = 0L;

  public static final long PRIORITY_NORMAL = 1L;

  public static final long PRIORITY_HIGH = 2L;

  public static final long PRIORITY_URGENT = 3L;

  public static final long SCOPE_LOCAL = 0L;

  public static final long SCOPE_GLOBAL = 1L;

  public static final long SCOPE_BOUND = 2L;

  public static final long STATE_JOINABLE = 0L;

  public static final long STATE_UNJOINABLE = 1L;

  public void join();

  public void interrupt();

  public long getPriority();

  public void setPriority(long arg1);

  public long getScope();

  public long getState();

  public void init(nsIRunnable arg1, long arg2, long arg3, long arg4, long arg5);

  public nsIThread getCurrentThread();

  public void sleep(long arg1);

}
