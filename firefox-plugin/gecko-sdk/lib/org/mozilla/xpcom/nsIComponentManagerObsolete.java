/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIComponentManager">
 **/

package org.mozilla.xpcom;

public interface nsIComponentManagerObsolete extends nsISupports
{
  public static final String NS_ICOMPONENTMANAGEROBSOLETE_IID =
    "{8458a740-d5dc-11d2-92fb-00e09805570f}";

  public static final int NS_Startup = 0;

  public static final int NS_Script = 1;

  public static final int NS_Timer = 2;

  public static final int NS_Shutdown = 3;

  public nsIFactory findFactory(String arg1);

  public String cLSIDToContractID(String arg1, String[] arg2);

  public String registryLocationForSpec(nsIFile arg1);

  public nsIFile specForRegistryLocation(String arg1);

  public void registerFactory(String arg1, String arg2, String arg3, nsIFactory arg4, boolean arg5);

  public void registerComponent(String arg1, String arg2, String arg3, String arg4, boolean arg5, boolean arg6);

  public void registerComponentWithType(String arg1, String arg2, String arg3, nsIFile arg4, String arg5, boolean arg6, boolean arg7, String arg8);

  public void registerComponentSpec(String arg1, String arg2, String arg3, nsIFile arg4, boolean arg5, boolean arg6);

  public void registerComponentLib(String arg1, String arg2, String arg3, String arg4, boolean arg5, boolean arg6);

  public void unregisterFactory(String arg1, nsIFactory arg2);

  public void unregisterComponent(String arg1, String arg2);

  public void unregisterComponentSpec(String arg1, nsIFile arg2);

  public void freeLibraries();

  public void autoRegister(int arg1, nsIFile arg2);

  public void autoRegisterComponent(int arg1, nsIFile arg2);

  public void autoUnregisterComponent(int arg1, nsIFile arg2);

  public boolean isRegistered(String arg1);

  public nsIEnumerator enumerateCLSIDs();

  public nsIEnumerator enumerateContractIDs();

}
