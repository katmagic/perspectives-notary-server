/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIExceptionManager">
 **/

package org.mozilla.xpcom;

public interface nsIExceptionManager extends nsISupports
{
  public static final String NS_IEXCEPTIONMANAGER_IID =
    "{efc9d00b-231c-4feb-852c-ac017266a415}";

  public void setCurrentException(nsIException arg1);

  public nsIException getCurrentException();

  public nsIException getExceptionFromProvider(long arg1, nsIException arg2);

}
