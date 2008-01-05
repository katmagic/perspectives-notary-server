/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsISocketTransport">
 **/

package org.mozilla.xpcom;

public interface nsISocketTransport extends nsITransport
{
  public static final String NS_ISOCKETTRANSPORT_IID =
    "{66418cc8-5f5d-4f52-a7f9-db8fb3b2cfe6}";

  public static final long TIMEOUT_CONNECT = 0L;

  public static final long TIMEOUT_READ_WRITE = 1L;

  public static final long STATUS_RESOLVING = 2152398851L;

  public static final long STATUS_CONNECTING_TO = 2152398855L;

  public static final long STATUS_CONNECTED_TO = 2152398852L;

  public static final long STATUS_SENDING_TO = 2152398853L;

  public static final long STATUS_WAITING_FOR = 2152398858L;

  public static final long STATUS_RECEIVING_FROM = 2152398854L;

  public String getHost();

  public int getPort();

  public nsISupports getSecurityInfo();

  public nsIInterfaceRequestor getSecurityCallbacks();

  public void setSecurityCallbacks(nsIInterfaceRequestor arg1);

  public boolean isAlive();

  public long getTimeout(long arg1);

  public void setTimeout(long arg1, long arg2);

}
