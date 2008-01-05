/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIWebServiceCallCo">
 **/

package org.mozilla.xpcom;

public interface nsIWebServiceCallContext extends nsISupports
{
  public static final String NS_IWEBSERVICECALLCONTEXT_IID =
    "{87d87900-f102-4a15-b345-7b77a49d2df2}";

  public static final long PENDING = 0L;

  public static final long SUCCEEDED = 1L;

  public static final long FAILED = 2L;

  public static final long ABORTED = 3L;

  public nsIWebServiceProxy getProxy();

  public String getMethodName();

  public long getStatus();

  public nsIException getPendingException();

  public nsIWSDLOperation getOperation();

  public void abort(nsIException arg1);

}
