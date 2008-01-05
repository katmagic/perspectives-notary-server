/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+imgIRequest">
 **/

package org.mozilla.xpcom;

public interface imgIRequest extends nsIRequest
{
  public static final String IMGIREQUEST_IID =
    "{ccf705f6-1dd1-11b2-82ef-e18eccf7f7ec}";

  public static final int STATUS_NONE = 0;

  public static final int STATUS_SIZE_AVAILABLE = 1;

  public static final int STATUS_LOAD_PARTIAL = 2;

  public static final int STATUS_LOAD_COMPLETE = 4;

  public static final int STATUS_ERROR = 8;

  public static final int STATUS_FRAME_COMPLETE = 16;

  public imgIContainer getImage();

  public long getImageStatus();

  public nsIURI getURI();

  public imgIDecoderObserver getDecoderObserver();

  public String getMimeType();

  public imgIRequest clone_(imgIDecoderObserver arg1);

}
