/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIIncrementalDownl">
 **/

package org.mozilla.xpcom;

public interface nsIIncrementalDownload extends nsIRequest
{
  public static final String NS_IINCREMENTALDOWNLOAD_IID =
    "{6687823f-56c4-461d-93a1-7f6cb7dfbfba}";

  public void init(nsIURI arg1, nsIFile arg2, int arg3, int arg4);

  public nsIURI getURI();

  public nsIURI getFinalURI();

  public nsIFile getDestination();

  public long getTotalSize();

  public long getCurrentSize();

  public void start(nsIRequestObserver arg1, nsISupports arg2);

}
