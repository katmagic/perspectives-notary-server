/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIObserverService">
 **/

package org.mozilla.xpcom;

public interface nsIObserverService extends nsISupports
{
  public static final String NS_IOBSERVERSERVICE_IID =
    "{d07f5192-e3d1-11d2-8acd-00105a1b8860}";

  public void addObserver(nsIObserver arg1, String arg2, boolean arg3);

  public void removeObserver(nsIObserver arg1, String arg2);

  public void notifyObservers(nsISupports arg1, String arg2, String arg3);

  public nsISimpleEnumerator enumerateObservers(String arg1);

}
