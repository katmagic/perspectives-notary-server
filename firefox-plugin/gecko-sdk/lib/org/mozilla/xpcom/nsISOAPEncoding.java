/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsISOAPEncoding">
 **/

package org.mozilla.xpcom;

public interface nsISOAPEncoding extends nsISupports
{
  public static final String NS_ISOAPENCODING_IID =
    "{9ae49600-1dd1-11b2-877f-e62f620c5e92}";

  public String getStyleURI();

  public nsISOAPEncoding getAssociatedEncoding(String arg1, boolean arg2);

  public void setEncoder(String arg1, nsISOAPEncoder arg2);

  public nsISOAPEncoder getEncoder(String arg1);

  public void setDecoder(String arg1, nsISOAPDecoder arg2);

  public nsISOAPDecoder getDecoder(String arg1);

  public nsISOAPEncoder getDefaultEncoder();

  public void setDefaultEncoder(nsISOAPEncoder arg1);

  public nsISOAPDecoder getDefaultDecoder();

  public void setDefaultDecoder(nsISOAPDecoder arg1);

  public nsISchemaCollection getSchemaCollection();

  public void setSchemaCollection(nsISchemaCollection arg1);

  public nsIDOMElement encode(nsIVariant arg1, String arg2, String arg3, nsISchemaType arg4, nsISOAPAttachments arg5, nsIDOMElement arg6);

  public nsIVariant decode(nsIDOMElement arg1, nsISchemaType arg2, nsISOAPAttachments arg3);

  public boolean mapSchemaURI(String arg1, String arg2, boolean arg3);

  public boolean unmapSchemaURI(String arg1);

  public String getInternalSchemaURI(String arg1);

  public String getExternalSchemaURI(String arg1);

}
