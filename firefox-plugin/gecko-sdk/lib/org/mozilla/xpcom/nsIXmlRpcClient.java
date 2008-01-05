/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIXmlRpcClient">
 **/

package org.mozilla.xpcom;

public interface nsIXmlRpcClient extends nsISupports
{
  public static final String NS_IXMLRPCCLIENT_IID =
    "{37127241-1e6e-46aa-ba87-601d41bb47df}";

  public static final long INT = 1L;

  public static final long BOOLEAN = 2L;

  public static final long STRING = 3L;

  public static final long DOUBLE = 4L;

  public static final long DATETIME = 5L;

  public static final long ARRAY = 6L;

  public static final long STRUCT = 7L;

  public void init(String arg1);

  public void setAuthentication(String arg1, String arg2);

  public void clearAuthentication(String arg1, String arg2);

  public nsIURL getServerURL();

  public void asyncCall(nsIXmlRpcClientListener arg1, nsISupports arg2, String arg3, nsISupports[] arg4, long arg5);

  public boolean getInProgress();

  public nsIXmlRpcFault getFault();

  public nsISupports getResult();

  public long getResponseStatus();

  public long getResponseString();

  public nsISupports createType(long arg1, String[] arg2);

}
