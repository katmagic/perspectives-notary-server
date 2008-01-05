/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIBaseWindow">
 **/

package org.mozilla.xpcom;

public interface nsIBaseWindow extends nsISupports
{
  public static final String NS_IBASEWINDOW_IID =
    "{046bc8a0-8015-11d3-af70-00a024ffc08c}";

  public void initWindow(long arg1, long arg2, int arg3, int arg4, int arg5, int arg6);

  public void create();

  public void destroy();

  public void setPosition(int arg1, int arg2);

  public void getPosition(int[] arg1, int[] arg2);

  public void setSize(int arg1, int arg2, boolean arg3);

  public void getSize(int[] arg1, int[] arg2);

  public void setPositionAndSize(int arg1, int arg2, int arg3, int arg4, boolean arg5);

  public void getPositionAndSize(int[] arg1, int[] arg2, int[] arg3, int[] arg4);

  public void repaint(boolean arg1);

  public long getParentWidget();

  public void setParentWidget(long arg1);

  public long getParentNativeWindow();

  public void setParentNativeWindow(long arg1);

  public boolean getVisibility();

  public void setVisibility(boolean arg1);

  public boolean getEnabled();

  public void setEnabled(boolean arg1);

  public boolean getBlurSuppression();

  public void setBlurSuppression(boolean arg1);

  public long getMainWidget();

  public void setFocus();

  public String getTitle();

  public void setTitle(String arg1);

}
