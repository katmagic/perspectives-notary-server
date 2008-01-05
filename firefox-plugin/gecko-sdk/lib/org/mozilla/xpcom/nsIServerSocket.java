/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIServerSocket">
 **/

package org.mozilla.xpcom;

public interface nsIServerSocket extends nsISupports
{
  public static final String NS_ISERVERSOCKET_IID =
    "{a5b64be0-d563-46bb-ae95-132e46fcd42f}";

  public void init(int arg1, boolean arg2, int arg3);

  public void close();

  public void asyncListen(nsIServerSocketListener arg1);

  public int getPort();

}
