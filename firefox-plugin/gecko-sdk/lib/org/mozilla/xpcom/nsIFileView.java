/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIFileView">
 **/

package org.mozilla.xpcom;

public interface nsIFileView extends nsISupports
{
  public static final String NS_IFILEVIEW_IID =
    "{60b320d2-1dd2-11b2-bd73-dc3575f78ddd}";

  public static final short sortName = 0;

  public static final short sortSize = 1;

  public static final short sortDate = 2;

  public boolean getShowHiddenFiles();

  public void setShowHiddenFiles(boolean arg1);

  public boolean getShowOnlyDirectories();

  public void setShowOnlyDirectories(boolean arg1);

  public short getSortType();

  public boolean getReverseSort();

  public void sort(short arg1, boolean arg2);

  public void setDirectory(nsIFile arg1);

  public void setFilter(String arg1);

  public nsIArray getSelectedFiles();

}
