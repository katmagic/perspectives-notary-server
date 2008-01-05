/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIServiceManager">
 **/

package org.mozilla.xpcom;

public interface nsIServiceManager extends nsISupports
{
  public static final String NS_ISERVICEMANAGER_IID =
    "{8bb35ed9-e332-462d-9155-4a002ab5c958}";

  public nsISupports getService(String arg1, String arg2);

  public nsISupports getServiceByContractID(String arg1, String arg2);

  public boolean isServiceInstantiated(String arg1, String arg2);

  public boolean isServiceInstantiatedByContractID(String arg1, String arg2);

}
