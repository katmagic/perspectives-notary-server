/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIHttpChannel">
 **/

package org.mozilla.xpcom;

public interface nsIHttpChannel extends nsIChannel
{
  public static final String NS_IHTTPCHANNEL_IID =
    "{9277fe09-f0cc-4cd9-bbce-581dd94b0260}";

  public String getRequestMethod();

  public void setRequestMethod(String arg1);

  public nsIURI getReferrer();

  public void setReferrer(nsIURI arg1);

  public String getRequestHeader(String arg1);

  public void setRequestHeader(String arg1, String arg2, boolean arg3);

  public void visitRequestHeaders(nsIHttpHeaderVisitor arg1);

  public boolean getAllowPipelining();

  public void setAllowPipelining(boolean arg1);

  public long getRedirectionLimit();

  public void setRedirectionLimit(long arg1);

  public long getResponseStatus();

  public String getResponseStatusText();

  public boolean getRequestSucceeded();

  public String getResponseHeader(String arg1);

  public void setResponseHeader(String arg1, String arg2, boolean arg3);

  public void visitResponseHeaders(nsIHttpHeaderVisitor arg1);

  public boolean isNoStoreResponse();

  public boolean isNoCacheResponse();

}
