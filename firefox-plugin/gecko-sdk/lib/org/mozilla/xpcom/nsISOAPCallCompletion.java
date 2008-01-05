/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsISOAPCallCompleti">
 **/

package org.mozilla.xpcom;

public interface nsISOAPCallCompletion extends nsISupports
{
  public static final String NS_ISOAPCALLCOMPLETION_IID =
    "{86114dd8-1dd2-11b2-ab2b-91d0c995e03a}";

  public nsISOAPCall getCall();

  public nsISOAPResponse getResponse();

  public nsISOAPResponseListener getListener();

  public boolean getIsComplete();

  public boolean abort();

}
