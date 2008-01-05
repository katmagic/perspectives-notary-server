/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIImageDocument">
 **/

package org.mozilla.xpcom;

public interface nsIImageDocument extends nsISupports
{
  public static final String NS_IIMAGEDOCUMENT_IID =
    "{7b80eebc-c98e-4461-8bdb-6e3b6e828890}";

  public boolean getImageResizingEnabled();

  public boolean getImageIsOverflowing();

  public boolean getImageIsResized();

  public imgIRequest getImageRequest();

  public void shrinkToFit();

  public void restoreImage();

  public void restoreImageTo(int arg1, int arg2);

  public void toggleImageSize();

}
