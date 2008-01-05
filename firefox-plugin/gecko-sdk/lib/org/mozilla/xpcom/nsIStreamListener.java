/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIStreamListener">
 **/

package org.mozilla.xpcom;

public interface nsIStreamListener extends nsIRequestObserver
{
  public static final String NS_ISTREAMLISTENER_IID =
    "{1a637020-1482-11d3-9333-00104ba0fd40}";

  public void onDataAvailable(nsIRequest arg1, nsISupports arg2, nsIInputStream arg3, long arg4, long arg5);

}
