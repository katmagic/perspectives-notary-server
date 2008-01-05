/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIProfileUnlocker">
 **/

package org.mozilla.xpcom;

public interface nsIProfileUnlocker extends nsISupports
{
  public static final String NS_IPROFILEUNLOCKER_IID =
    "{08923af1-e7a3-4fae-ba02-128502193994}";

  public static final long ATTEMPT_QUIT = 0L;

  public static final long FORCE_QUIT = 1L;

  public void unlock(long arg1);

}
