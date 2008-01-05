/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIModule">
 **/

package org.mozilla.xpcom;

public interface nsIModule extends nsISupports
{
  public static final String NS_IMODULE_IID =
    "{7392d032-5371-11d3-994e-00805fd26fee}";

  public nsISupports getClassObject(nsIComponentManager arg1, String arg2, String arg3);

  public void registerSelf(nsIComponentManager arg1, nsIFile arg2, String arg3, String arg4);

  public void unregisterSelf(nsIComponentManager arg1, nsIFile arg2, String arg3);

  public boolean canUnload(nsIComponentManager arg1);

}
