/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIRemoteService">
 **/

package org.mozilla.xpcom;

public interface nsIRemoteService extends nsISupports
{
  public static final String NS_IREMOTESERVICE_IID =
    "{a2240f6a-f1e4-4548-9e1a-6f3bc9b2426c}";

  public void startup(String arg1, String arg2);

  public void registerWindow(nsIDOMWindow arg1);

  public void shutdown();

}
