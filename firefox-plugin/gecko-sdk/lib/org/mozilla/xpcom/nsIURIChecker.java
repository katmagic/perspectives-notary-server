/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIURIChecker">
 **/

package org.mozilla.xpcom;

public interface nsIURIChecker extends nsIRequest
{
  public static final String NS_IURICHECKER_IID =
    "{4660c1a1-be2d-4c78-9baf-c22984176c28}";

  public void init(nsIURI arg1);

  public nsIChannel getBaseChannel();

  public void asyncCheck(nsIRequestObserver arg1, nsISupports arg2);

}
