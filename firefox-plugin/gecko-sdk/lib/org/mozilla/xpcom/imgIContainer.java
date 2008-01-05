/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+imgIContainer">
 **/

package org.mozilla.xpcom;

public interface imgIContainer extends nsISupports
{
  public static final String IMGICONTAINER_IID =
    "{1a6290e6-8285-4e10-963d-d001f8d327b8}";

  public static final short kNormalAnimMode = 0;

  public static final short kDontAnimMode = 1;

  public static final short kLoopOnceAnimMode = 2;

  public void init(int arg1, int arg2, nsISupports arg3);

  public int getPreferredAlphaChannelFormat();

  public int getWidth();

  public int getHeight();

  public gfxIImageFrame getCurrentFrame();

  public long getNumFrames();

  public int getAnimationMode();

  public void setAnimationMode(int arg1);

  public gfxIImageFrame getFrameAt(long arg1);

  public void appendFrame(gfxIImageFrame arg1);

  public void removeFrame(gfxIImageFrame arg1);

  public void endFrameDecode(long arg1, long arg2);

  public void decodingComplete();

  public void clear();

  public void startAnimation();

  public void stopAnimation();

  public void resetAnimation();

  public int getLoopCount();

  public void setLoopCount(int arg1);

}
