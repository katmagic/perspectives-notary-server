/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIURI">
 **/

package org.mozilla.xpcom;

public interface nsIURI extends nsISupports
{
  public static final String NS_IURI_IID =
    "{07a22cc0-0ce5-11d3-9331-00104ba0fd40}";

  public String getSpec();

  public void setSpec(String arg1);

  public String getPrePath();

  public String getScheme();

  public void setScheme(String arg1);

  public String getUserPass();

  public void setUserPass(String arg1);

  public String getUsername();

  public void setUsername(String arg1);

  public String getPassword();

  public void setPassword(String arg1);

  public String getHostPort();

  public void setHostPort(String arg1);

  public String getHost();

  public void setHost(String arg1);

  public int getPort();

  public void setPort(int arg1);

  public String getPath();

  public void setPath(String arg1);

  public boolean equals(nsIURI arg1);

  public boolean schemeIs(String arg1);

  public nsIURI clone_();

  public String resolve(String arg1);

  public String getAsciiSpec();

  public String getAsciiHost();

  public String getOriginCharset();

}
