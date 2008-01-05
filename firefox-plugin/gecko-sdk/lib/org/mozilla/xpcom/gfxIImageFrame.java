/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+gfxIImageFrame">
 **/

package org.mozilla.xpcom;

public interface gfxIImageFrame extends nsISupports
{
  public static final String GFXIIMAGEFRAME_IID =
    "{f6d00ee7-defc-4101-b2dc-e72cf4c37c3c}";

  public void init(int arg1, int arg2, int arg3, int arg4, int arg5, int arg6);

  public boolean getMutable();

  public void setMutable(boolean arg1);

  public int getX();

  public int getY();

  public int getWidth();

  public int getHeight();

  public int getFormat();

  public boolean getNeedsBackground();

  public long getImageBytesPerRow();

  public long getImageDataLength();

  public void getImageData(short[][] arg1, long[] arg2);

  public void setImageData(short[] arg1, long arg2, int arg3);

  public void lockImageData();

  public void unlockImageData();

  public long getAlphaBytesPerRow();

  public long getAlphaDataLength();

  public void getAlphaData(short[][] arg1, long[] arg2);

  public void setAlphaData(short[] arg1, long arg2, int arg3);

  public void lockAlphaData();

  public void unlockAlphaData();

  public void drawTo(gfxIImageFrame arg1, int arg2, int arg3, int arg4, int arg5);

  public int getTimeout();

  public void setTimeout(int arg1);

  public int getFrameDisposalMethod();

  public void setFrameDisposalMethod(int arg1);

  public long getBackgroundColor();

  public void setBackgroundColor(long arg1);

}
