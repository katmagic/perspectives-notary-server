/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsISelectionDisplay">
 **/

package org.mozilla.xpcom;

public interface nsISelectionDisplay extends nsISupports
{
  public static final String NS_ISELECTIONDISPLAY_IID =
    "{0ddf9e1c-1dd2-11b2-a183-908a08aa75ae}";

  public static final short DISPLAY_TEXT = 1;

  public static final short DISPLAY_IMAGES = 2;

  public static final short DISPLAY_FRAMES = 4;

  public static final short DISPLAY_ALL = 7;

  public void setSelectionFlags(short arg1);

  public short getSelectionFlags();

}
