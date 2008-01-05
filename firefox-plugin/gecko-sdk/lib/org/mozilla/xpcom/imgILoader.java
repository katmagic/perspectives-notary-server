/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+imgILoader">
 **/

package org.mozilla.xpcom;

public interface imgILoader extends nsISupports
{
  public static final String IMGILOADER_IID =
    "{a32826ff-9e56-4425-a811-97a8dba64ff5}";

  public imgIRequest loadImage(nsIURI arg1, nsIURI arg2, nsIURI arg3, nsILoadGroup arg4, imgIDecoderObserver arg5, nsISupports arg6, long arg7, nsISupports arg8, imgIRequest arg9);

  public imgIRequest loadImageWithChannel(nsIChannel arg1, imgIDecoderObserver arg2, nsISupports arg3, nsIStreamListener[] arg4);

  public boolean supportImageWithMimeType(String arg1);

}
