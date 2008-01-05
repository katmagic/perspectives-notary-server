/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsICacheListener">
 **/

package org.mozilla.xpcom;

public interface nsICacheListener extends nsISupports
{
  public static final String NS_ICACHELISTENER_IID =
    "{638c3848-778b-4851-8ff3-9400f65b8773}";

  public void onCacheEntryAvailable(nsICacheEntryDescriptor arg1, int arg2, long arg3);

}
