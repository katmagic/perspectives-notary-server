/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIExtensionManager">
 **/

package org.mozilla.xpcom;

public interface nsIExtensionManager extends nsISupports
{
  public static final String NS_IEXTENSIONMANAGER_IID =
    "{a3f5396c-a6e8-414a-8fbc-c8d831746328}";

  public boolean start(nsICommandLine arg1);

  public boolean checkForMismatches();

  public void handleCommandLineArgs(nsICommandLine arg1);

  public nsIInstallLocation getInstallLocation(String arg1);

  public nsISimpleEnumerator getInstallLocations();

  public void installItemFromFile(nsIFile arg1, String arg2);

  public void uninstallItem(String arg1);

  public void enableItem(String arg1);

  public void disableItem(String arg1);

  public void update(nsIUpdateItem[] arg1, long arg2, long arg3, nsIAddonUpdateCheckListener arg4);

  public nsIUpdateItem getItemForID(String arg1);

  public nsIUpdateItem[] getItemList(long arg1, long[] arg2);

  public nsIUpdateItem[] getIncompatibleItemList(String arg1, String arg2, long arg3, boolean arg4, long[] arg5);

  public nsIRDFDataSource getDatasource();

  public void addDownloads(nsIUpdateItem[] arg1, long arg2, boolean arg3);

  public void removeDownload(String arg1);

  public int addUpdateListener(nsIAddonUpdateListener arg1);

  public void removeUpdateListenerAt(int arg1);

  public void moveToIndexOf(String arg1, String arg2);

}
