/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIDOMLSInput">
 **/

package org.mozilla.xpcom;

public interface nsIDOMLSInput extends nsISupports
{
  public static final String NS_IDOMLSINPUT_IID =
    "{165e7f61-5048-4c2c-b4bf-6b44bb617ee4}";

  public nsISupports getCharacterStream();

  public void setCharacterStream(nsISupports arg1);

  public nsIInputStream getByteStream();

  public void setByteStream(nsIInputStream arg1);

  public String getStringData();

  public void setStringData(String arg1);

  public String getSystemId();

  public void setSystemId(String arg1);

  public String getPublicId();

  public void setPublicId(String arg1);

  public String getBaseURI();

  public void setBaseURI(String arg1);

  public String getEncoding();

  public void setEncoding(String arg1);

  public boolean getCertifiedText();

  public void setCertifiedText(boolean arg1);

}
