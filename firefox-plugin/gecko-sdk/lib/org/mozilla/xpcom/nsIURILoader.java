/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIURILoader">
 **/

package org.mozilla.xpcom;

public interface nsIURILoader extends nsISupports
{
  public static final String NS_IURILOADER_IID =
    "{5cf6420c-74f3-4a7c-bc1d-f5756d79ea07}";

  public void registerContentListener(nsIURIContentListener arg1);

  public void unRegisterContentListener(nsIURIContentListener arg1);

  public void openURI(nsIChannel arg1, boolean arg2, nsIInterfaceRequestor arg3);

  public void stop(nsISupports arg1);

}
