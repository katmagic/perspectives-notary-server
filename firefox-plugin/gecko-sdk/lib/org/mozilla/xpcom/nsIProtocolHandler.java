/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIProtocolHandler">
 **/

package org.mozilla.xpcom;

public interface nsIProtocolHandler extends nsISupports
{
  public static final String NS_IPROTOCOLHANDLER_IID =
    "{15fd6940-8ea7-11d3-93ad-00104ba0fd40}";

  public static final long URI_STD = 0L;

  public static final long URI_NORELATIVE = 1L;

  public static final long URI_NOAUTH = 2L;

  public static final long ALLOWS_PROXY = 4L;

  public static final long ALLOWS_PROXY_HTTP = 8L;

  public String getScheme();

  public int getDefaultPort();

  public long getProtocolFlags();

  public nsIURI newURI(String arg1, String arg2, nsIURI arg3);

  public nsIChannel newChannel(nsIURI arg1);

  public boolean allowPort(int arg1, String arg2);

}
