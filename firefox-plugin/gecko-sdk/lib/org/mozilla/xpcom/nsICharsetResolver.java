/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsICharsetResolver">
 **/

package org.mozilla.xpcom;

public interface nsICharsetResolver extends nsISupports
{
  public static final String NS_ICHARSETRESOLVER_IID =
    "{d143a084-b626-4614-845f-41f3ca43a674}";

  public String requestCharset(nsIWebNavigation arg1, nsIChannel arg2, boolean[] arg3, nsISupports[] arg4);

  public void notifyResolvedCharset(String arg1, nsISupports arg2);

}
