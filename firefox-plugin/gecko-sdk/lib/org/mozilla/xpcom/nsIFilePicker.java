/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIFilePicker">
 **/

package org.mozilla.xpcom;

public interface nsIFilePicker extends nsISupports
{
  public static final String NS_IFILEPICKER_IID =
    "{80faf095-c807-4558-a2cc-185ed70754ea}";

  public static final short modeOpen = 0;

  public static final short modeSave = 1;

  public static final short modeGetFolder = 2;

  public static final short modeOpenMultiple = 3;

  public static final short returnOK = 0;

  public static final short returnCancel = 1;

  public static final short returnReplace = 2;

  public static final int filterAll = 1;

  public static final int filterHTML = 2;

  public static final int filterText = 4;

  public static final int filterImages = 8;

  public static final int filterXML = 16;

  public static final int filterXUL = 32;

  public static final int filterApps = 64;

  public void init(nsIDOMWindow arg1, String arg2, short arg3);

  public void appendFilters(int arg1);

  public void appendFilter(String arg1, String arg2);

  public String getDefaultString();

  public void setDefaultString(String arg1);

  public String getDefaultExtension();

  public void setDefaultExtension(String arg1);

  public int getFilterIndex();

  public void setFilterIndex(int arg1);

  public nsILocalFile getDisplayDirectory();

  public void setDisplayDirectory(nsILocalFile arg1);

  public nsILocalFile getFile();

  public nsIFileURL getFileURL();

  public nsISimpleEnumerator getFiles();

  public short show();

}
