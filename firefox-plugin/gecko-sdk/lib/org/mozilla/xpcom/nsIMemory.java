/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIMemory">
 **/

package org.mozilla.xpcom;

public interface nsIMemory extends nsISupports
{
  public static final String NS_IMEMORY_IID =
    "{59e7e77a-38e4-11d4-8cf5-0060b0fc14a3}";

  public void heapMinimize(boolean arg1);

  public boolean isLowMemory();

}
