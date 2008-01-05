/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIRequest">
 **/

package org.mozilla.xpcom;

public interface nsIRequest extends nsISupports
{
  public static final String NS_IREQUEST_IID =
    "{ef6bfbd2-fd46-48d8-96b7-9f8f0fd387fe}";

  public static final long LOAD_NORMAL = 0L;

  public static final long LOAD_BACKGROUND = 1L;

  public static final long INHIBIT_CACHING = 128L;

  public static final long INHIBIT_PERSISTENT_CACHING = 256L;

  public static final long LOAD_BYPASS_CACHE = 512L;

  public static final long LOAD_FROM_CACHE = 1024L;

  public static final long VALIDATE_ALWAYS = 2048L;

  public static final long VALIDATE_NEVER = 4096L;

  public static final long VALIDATE_ONCE_PER_SESSION = 8192L;

  public String getName();

  public boolean isPending();

  public long getStatus();

  public void cancel(long arg1);

  public void suspend();

  public void resume();

  public nsILoadGroup getLoadGroup();

  public void setLoadGroup(nsILoadGroup arg1);

  public long getLoadFlags();

  public void setLoadFlags(long arg1);

}
