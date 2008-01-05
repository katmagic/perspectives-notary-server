/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIDOMNSDocument">
 **/

package org.mozilla.xpcom;

public interface nsIDOMNSDocument extends nsISupports
{
  public static final String NS_IDOMNSDOCUMENT_IID =
    "{a6cf90cd-15b3-11d2-932e-00805f8add32}";

  public String getCharacterSet();

  public String getDir();

  public void setDir(String arg1);

  public nsIDOMLocation getLocation();

  public String getTitle();

  public void setTitle(String arg1);

  public String getContentType();

  public String getLastModified();

  public String getReferrer();

  public nsIBoxObject getBoxObjectFor(nsIDOMElement arg1);

  public void setBoxObjectFor(nsIDOMElement arg1, nsIBoxObject arg2);

}
