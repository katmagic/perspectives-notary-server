/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIContentViewerEdi">
 **/

package org.mozilla.xpcom;

public interface nsIContentViewerEdit extends nsISupports
{
  public static final String NS_ICONTENTVIEWEREDIT_IID =
    "{1691a02f-53b2-4cb8-8769-48e7efc908b8}";

  public static final int COPY_IMAGE_TEXT = 1;

  public static final int COPY_IMAGE_HTML = 2;

  public static final int COPY_IMAGE_DATA = 4;

  public static final int COPY_IMAGE_ALL = -1;

  public void search();

  public boolean getSearchable();

  public void clearSelection();

  public void selectAll();

  public void copySelection();

  public boolean getCopyable();

  public void copyLinkLocation();

  public boolean getInLink();

  public void copyImage(int arg1);

  public boolean getInImage();

  public void cutSelection();

  public boolean getCutable();

  public void paste();

  public boolean getPasteable();

  public String getContents(String arg1, boolean arg2);

  public boolean getCanGetContents();

}
