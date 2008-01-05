/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIExceptionService">
 **/

package org.mozilla.xpcom;

public interface nsIExceptionService extends nsIExceptionManager
{
  public static final String NS_IEXCEPTIONSERVICE_IID =
    "{35a88f54-f267-4414-92a7-191f6454ab52}";

  public nsIExceptionManager getCurrentExceptionManager();

  public void registerExceptionProvider(nsIExceptionProvider arg1, long arg2);

  public void unregisterExceptionProvider(nsIExceptionProvider arg1, long arg2);

}
