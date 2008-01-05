/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIComponentRegistr">
 **/

package org.mozilla.xpcom;

public interface nsIComponentRegistrar extends nsISupports
{
  public static final String NS_ICOMPONENTREGISTRAR_IID =
    "{2417cbfe-65ad-48a6-b4b6-eb84db174392}";

  public void autoRegister(nsIFile arg1);

  public void autoUnregister(nsIFile arg1);

  public void registerFactory(String arg1, String arg2, String arg3, nsIFactory arg4);

  public void unregisterFactory(String arg1, nsIFactory arg2);

  public void registerFactoryLocation(String arg1, String arg2, String arg3, nsIFile arg4, String arg5, String arg6);

  public void unregisterFactoryLocation(String arg1, nsIFile arg2);

  public boolean isCIDRegistered(String arg1);

  public boolean isContractIDRegistered(String arg1);

  public nsISimpleEnumerator enumerateCIDs();

  public nsISimpleEnumerator enumerateContractIDs();

  public String cIDToContractID(String arg1);

  public String contractIDToCID(String arg1);

}
