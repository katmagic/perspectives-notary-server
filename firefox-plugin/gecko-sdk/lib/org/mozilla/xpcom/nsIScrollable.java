/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIScrollable">
 **/

package org.mozilla.xpcom;

public interface nsIScrollable extends nsISupports
{
  public static final String NS_ISCROLLABLE_IID =
    "{919e792a-6490-40b8-bba5-f9e9ad5640c8}";

  public static final int ScrollOrientation_X = 1;

  public static final int ScrollOrientation_Y = 2;

  public static final int Scrollbar_Auto = 1;

  public static final int Scrollbar_Never = 2;

  public static final int Scrollbar_Always = 3;

  public int getCurScrollPos(int arg1);

  public void setCurScrollPos(int arg1, int arg2);

  public void setCurScrollPosEx(int arg1, int arg2);

  public void getScrollRange(int arg1, int[] arg2, int[] arg3);

  public void setScrollRange(int arg1, int arg2, int arg3);

  public void setScrollRangeEx(int arg1, int arg2, int arg3, int arg4);

  public int getDefaultScrollbarPreferences(int arg1);

  public void setDefaultScrollbarPreferences(int arg1, int arg2);

  public void getScrollbarVisibility(boolean[] arg1, boolean[] arg2);

}
