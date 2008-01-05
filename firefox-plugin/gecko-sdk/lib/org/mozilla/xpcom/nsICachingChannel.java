/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsICachingChannel">
 **/

package org.mozilla.xpcom;

public interface nsICachingChannel extends nsISupports
{
  public static final String NS_ICACHINGCHANNEL_IID =
    "{b1f95f5e-ee05-4434-9d34-89a935d7feef}";

  public static final long LOAD_BYPASS_LOCAL_CACHE = 268435456L;

  public static final long LOAD_BYPASS_LOCAL_CACHE_IF_BUSY = 536870912L;

  public static final long LOAD_ONLY_FROM_CACHE = 1073741824L;

  public static final long LOAD_ONLY_IF_MODIFIED = 2147483648L;

  public nsISupports getCacheToken();

  public void setCacheToken(nsISupports arg1);

  public nsISupports getCacheKey();

  public void setCacheKey(nsISupports arg1);

  public boolean getCacheAsFile();

  public void setCacheAsFile(boolean arg1);

  public nsIFile getCacheFile();

  public boolean isFromCache();

}
