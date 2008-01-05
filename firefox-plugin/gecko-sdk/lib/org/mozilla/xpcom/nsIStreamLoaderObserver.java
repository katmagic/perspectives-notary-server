/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIStreamLoaderObse">
 **/

package org.mozilla.xpcom;

public interface nsIStreamLoaderObserver extends nsISupports
{
  public static final String NS_ISTREAMLOADEROBSERVER_IID =
    "{359f7990-d4e9-11d3-a1a5-0050041caf44}";

  public void onStreamComplete(nsIStreamLoader arg1, nsISupports arg2, long arg3, long arg4, short[] arg5);

}
