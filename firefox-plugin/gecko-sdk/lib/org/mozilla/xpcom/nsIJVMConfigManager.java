/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIJVMConfigManager">
 **/

package org.mozilla.xpcom;

public interface nsIJVMConfigManager extends nsISupports
{
  public static final String NS_IJVMCONFIGMANAGER_IID =
    "{ca29fff1-a677-493c-9d80-3dc60432212b}";

  public nsIArray getJVMConfigList();

  public void setCurrentJVMConfig(nsIJVMConfig arg1);

}
