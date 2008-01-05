/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIComponentManager">
 **/

package org.mozilla.xpcom;

public interface nsIComponentManager extends nsISupports
{
  public static final String NS_ICOMPONENTMANAGER_IID =
    "{a88e5a60-205a-4bb1-94e1-2628daf51eae}";

  public nsISupports getClassObject(String arg1, String arg2);

  public nsISupports getClassObjectByContractID(String arg1, String arg2);

  public nsISupports createInstance(String arg1, nsISupports arg2, String arg3);

  public nsISupports createInstanceByContractID(String arg1, nsISupports arg2, String arg3);

}
