/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIDOMLocation">
 **/

package org.mozilla.xpcom;

public interface nsIDOMLocation extends nsISupports
{
  public static final String NS_IDOMLOCATION_IID =
    "{a6cf906d-15b3-11d2-932e-00805f8add32}";

  public String getHash();

  public void setHash(String arg1);

  public String getHost();

  public void setHost(String arg1);

  public String getHostname();

  public void setHostname(String arg1);

  public String getHref();

  public void setHref(String arg1);

  public String getPathname();

  public void setPathname(String arg1);

  public String getPort();

  public void setPort(String arg1);

  public String getProtocol();

  public void setProtocol(String arg1);

  public String getSearch();

  public void setSearch(String arg1);

  public void replace(String arg1);

  public void assign(String arg1);

  public String toString();

}
