/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIDOMHTMLDocument">
 **/

package org.mozilla.xpcom;

public interface nsIDOMHTMLDocument extends nsIDOMDocument
{
  public static final String NS_IDOMHTMLDOCUMENT_IID =
    "{a6cf9084-15b3-11d2-932e-00805f8add32}";

  public String getTitle();

  public void setTitle(String arg1);

  public String getReferrer();

  public String getURL();

  public nsIDOMHTMLElement getBody();

  public void setBody(nsIDOMHTMLElement arg1);

  public nsIDOMHTMLCollection getImages();

  public nsIDOMHTMLCollection getApplets();

  public nsIDOMHTMLCollection getLinks();

  public nsIDOMHTMLCollection getForms();

  public nsIDOMHTMLCollection getAnchors();

  public String getCookie();

  public void setCookie(String arg1);

  public void close();

  public nsIDOMNodeList getElementsByName(String arg1);

}
