/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIUnicharStreamLoa">
 **/

package org.mozilla.xpcom;

public interface nsIUnicharStreamLoader extends nsISupports
{
  public static final String NS_IUNICHARSTREAMLOADER_IID =
    "{8a3eca16-167e-443d-9485-7e84ed822e95}";

  public static final long DEFAULT_SEGMENT_SIZE = 4096L;

  public void init(nsIChannel arg1, nsIUnicharStreamLoaderObserver arg2, nsISupports arg3, long arg4);

  public nsIChannel getChannel();

  public String getCharset();

}
