/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIPKCS11ModuleDB">
 **/

package org.mozilla.xpcom;

public interface nsIPKCS11ModuleDB extends nsISupports
{
  public static final String NS_IPKCS11MODULEDB_IID =
    "{ff9fbcd7-9517-4334-b97a-ceed78909974}";

  public nsIPKCS11Module getInternal();

  public nsIPKCS11Module getInternalFIPS();

  public nsIPKCS11Module findModuleByName(String arg1);

  public nsIPKCS11Slot findSlotByName(String arg1);

  public nsIEnumerator listModules();

  public boolean getCanToggleFIPS();

  public void toggleFIPSMode();

  public boolean getIsFIPSEnabled();

}
