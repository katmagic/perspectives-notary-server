/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIImageLoadingCont">
 **/

package org.mozilla.xpcom;

public interface nsIImageLoadingContent extends imgIDecoderObserver
{
  public static final String NS_IIMAGELOADINGCONTENT_IID =
    "{da19c86d-08aa-421c-8c37-12ec2ba5a2c3}";

  public static final int UNKNOWN_REQUEST = -1;

  public static final int CURRENT_REQUEST = 0;

  public static final int PENDING_REQUEST = 1;

  public boolean getLoadingEnabled();

  public void setLoadingEnabled(boolean arg1);

  public short getImageBlockingStatus();

  public void addObserver(imgIDecoderObserver arg1);

  public void removeObserver(imgIDecoderObserver arg1);

  public imgIRequest getRequest(int arg1);

  public int getRequestType(imgIRequest arg1);

  public nsIURI getCurrentURI();

  public nsIStreamListener loadImageWithChannel(nsIChannel arg1);

}
