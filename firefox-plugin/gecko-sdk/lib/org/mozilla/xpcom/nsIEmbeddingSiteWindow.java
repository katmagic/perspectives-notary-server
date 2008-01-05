/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIEmbeddingSiteWin">
 **/

package org.mozilla.xpcom;

public interface nsIEmbeddingSiteWindow extends nsISupports
{
  public static final String NS_IEMBEDDINGSITEWINDOW_IID =
    "{3e5432cd-9568-4bd1-8cbe-d50aba110743}";

  public static final long DIM_FLAGS_POSITION = 1L;

  public static final long DIM_FLAGS_SIZE_INNER = 2L;

  public static final long DIM_FLAGS_SIZE_OUTER = 4L;

  public void setDimensions(long arg1, int arg2, int arg3, int arg4, int arg5);

  public void getDimensions(long arg1, int[] arg2, int[] arg3, int[] arg4, int[] arg5);

  public void setFocus();

  public boolean getVisibility();

  public void setVisibility(boolean arg1);

  public String getTitle();

  public void setTitle(String arg1);

  public long getSiteWindow();

}
