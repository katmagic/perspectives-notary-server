/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIStreamLoader">
 **/

package org.mozilla.xpcom;

public interface nsIStreamLoader extends nsISupports
{
  public static final String NS_ISTREAMLOADER_IID =
    "{31d37360-8e5a-11d3-93ad-00104ba0fd40}";

  public void init(nsIChannel arg1, nsIStreamLoaderObserver arg2, nsISupports arg3);

  public long getNumBytesRead();

  public nsIRequest getRequest();

}
