/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIHttpEventSink">
 **/

package org.mozilla.xpcom;

public interface nsIHttpEventSink extends nsISupports
{
  public static final String NS_IHTTPEVENTSINK_IID =
    "{9475a6af-6352-4251-90f9-d65b1cd2ea15}";

  public void onRedirect(nsIHttpChannel arg1, nsIChannel arg2);

}
