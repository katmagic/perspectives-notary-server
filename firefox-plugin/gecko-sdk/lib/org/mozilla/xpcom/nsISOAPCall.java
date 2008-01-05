/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsISOAPCall">
 **/

package org.mozilla.xpcom;

public interface nsISOAPCall extends nsISOAPMessage
{
  public static final String NS_ISOAPCALL_IID =
    "{a8fefe40-52bc-11d4-9a57-000064657374}";

  public String getTransportURI();

  public void setTransportURI(String arg1);

  public boolean getVerifySourceHeader();

  public void setVerifySourceHeader(boolean arg1);

  public nsISOAPResponse invoke();

  public nsISOAPCallCompletion asyncInvoke(nsISOAPResponseListener arg1);

}
