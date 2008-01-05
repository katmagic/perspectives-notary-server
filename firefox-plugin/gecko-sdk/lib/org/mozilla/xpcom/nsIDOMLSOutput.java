/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIDOMLSOutput">
 **/

package org.mozilla.xpcom;

public interface nsIDOMLSOutput extends nsISupports
{
  public static final String NS_IDOMLSOUTPUT_IID =
    "{757e9971-8890-478d-a53a-07f9f6f6e0d3}";

  public nsISupports getCharacterStream();

  public void setCharacterStream(nsISupports arg1);

  public nsIOutputStream getByteStream();

  public void setByteStream(nsIOutputStream arg1);

  public String getSystemId();

  public void setSystemId(String arg1);

  public String getEncoding();

  public void setEncoding(String arg1);

}
