/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIUnicharStreamLis">
 **/

package org.mozilla.xpcom;

public interface nsIUnicharStreamListener extends nsIRequestObserver
{
  public static final String NS_IUNICHARSTREAMLISTENER_IID =
    "{4a7e9b62-fef8-400d-9865-d6820f630b4c}";

  public void onUnicharDataAvailable(nsIRequest arg1, nsISupports arg2, String arg3);

}
