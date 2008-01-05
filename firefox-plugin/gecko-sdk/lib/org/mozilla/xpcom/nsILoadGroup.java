/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsILoadGroup">
 **/

package org.mozilla.xpcom;

public interface nsILoadGroup extends nsIRequest
{
  public static final String NS_ILOADGROUP_IID =
    "{3de0a31c-feaf-400f-9f1e-4ef71f8b20cc}";

  public nsIRequestObserver getGroupObserver();

  public void setGroupObserver(nsIRequestObserver arg1);

  public nsIRequest getDefaultLoadRequest();

  public void setDefaultLoadRequest(nsIRequest arg1);

  public void addRequest(nsIRequest arg1, nsISupports arg2);

  public void removeRequest(nsIRequest arg1, nsISupports arg2, long arg3);

  public nsISimpleEnumerator getRequests();

  public long getActiveCount();

  public nsIInterfaceRequestor getNotificationCallbacks();

  public void setNotificationCallbacks(nsIInterfaceRequestor arg1);

}
