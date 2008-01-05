/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIScriptLoaderObse">
 **/

package org.mozilla.xpcom;

public interface nsIScriptLoaderObserver extends nsISupports
{
  public static final String NS_ISCRIPTLOADEROBSERVER_IID =
    "{501209d3-7edf-437d-9948-3c6d1c08ef7f}";

  public void scriptAvailable(long arg1, nsISupports arg2, boolean arg3, boolean arg4, nsIURI arg5, int arg6, String arg7);

  public void scriptEvaluated(long arg1, nsISupports arg2, boolean arg3, boolean arg4);

}
