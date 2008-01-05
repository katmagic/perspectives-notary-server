/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIHttpChannelInter">
 **/

package org.mozilla.xpcom;

public interface nsIHttpChannelInternal extends nsISupports
{
  public static final String NS_IHTTPCHANNELINTERNAL_IID =
    "{f3764874-ed7e-4873-883c-11d67a4e3638}";

  public nsIURI getDocumentURI();

  public void setDocumentURI(nsIURI arg1);

  public void getRequestVersion(long[] arg1, long[] arg2);

  public void getResponseVersion(long[] arg1, long[] arg2);

  public void setCookie(String arg1);

  public nsIProxyInfo getProxyInfo();

}
