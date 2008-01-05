/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsICacheSession">
 **/

package org.mozilla.xpcom;

public interface nsICacheSession extends nsISupports
{
  public static final String NS_ICACHESESSION_IID =
    "{ae9e84b5-3e2d-457e-8fcd-5bbd2a8b832e}";

  public boolean getDoomEntriesIfExpired();

  public void setDoomEntriesIfExpired(boolean arg1);

  public nsICacheEntryDescriptor openCacheEntry(String arg1, int arg2, boolean arg3);

  public void asyncOpenCacheEntry(String arg1, int arg2, nsICacheListener arg3);

  public void evictEntries();

  public boolean isStorageEnabled();

}
