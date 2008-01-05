/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+imgICache">
 **/

package org.mozilla.xpcom;

public interface imgICache extends nsISupports
{
  public static final String IMGICACHE_IID =
    "{f1b74aae-5661-4753-a21c-66dd644afebc}";

  public void clearCache(boolean arg1);

  public void removeEntry(nsIURI arg1);

  public nsIProperties findEntryProperties(nsIURI arg1);

}
