/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsITimer">
 **/

package org.mozilla.xpcom;

public interface nsITimer extends nsISupports
{
  public static final String NS_ITIMER_IID =
    "{436a83fa-b396-11d9-bcfa-00112478d626}";

  public static final short TYPE_ONE_SHOT = 0;

  public static final short TYPE_REPEATING_SLACK = 1;

  public static final short TYPE_REPEATING_PRECISE = 2;

  public void init(nsIObserver arg1, long arg2, long arg3);

  public void initWithCallback(nsITimerCallback arg1, long arg2, long arg3);

  public void cancel();

  public long getDelay();

  public void setDelay(long arg1);

  public long getType();

  public void setType(long arg1);

  public nsITimerCallback getCallback();

}
