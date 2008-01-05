/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+imgIDecoderObserver">
 **/

package org.mozilla.xpcom;

public interface imgIDecoderObserver extends imgIContainerObserver
{
  public static final String IMGIDECODEROBSERVER_IID =
    "{cce7152e-4395-4231-a781-c347c5446cc2}";

  public void onStartDecode(imgIRequest arg1);

  public void onStartContainer(imgIRequest arg1, imgIContainer arg2);

  public void onStartFrame(imgIRequest arg1, gfxIImageFrame arg2);

  public void onStopFrame(imgIRequest arg1, gfxIImageFrame arg2);

  public void onStopContainer(imgIRequest arg1, imgIContainer arg2);

  public void onStopDecode(imgIRequest arg1, long arg2, String arg3);

}
