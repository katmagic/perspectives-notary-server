/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIXPInstallManager">
 **/

package org.mozilla.xpcom;

public interface nsIXPInstallManagerUI extends nsISupports
{
  public static final String NS_IXPINSTALLMANAGERUI_IID =
    "{087f52a4-8fd8-40ab-ae52-c3e161810141}";

  public static final short INSTALL_DOWNLOADING = 5;

  public static final short INSTALL_INSTALLING = 6;

  public static final short INSTALL_FINISHED = 7;

  public static final short DOWNLOAD_TYPE_INSTALL = 1;

  public nsIXPIProgressDialog getXpiProgress();

  public boolean getHasActiveXPIOperations();

}
