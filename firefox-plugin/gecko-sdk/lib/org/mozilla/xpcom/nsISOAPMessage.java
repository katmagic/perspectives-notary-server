/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsISOAPMessage">
 **/

package org.mozilla.xpcom;

public interface nsISOAPMessage extends nsISupports
{
  public static final String NS_ISOAPMESSAGE_IID =
    "{3970815e-1dd2-11b2-a475-db4dac6826f1}";

  public static final int VERSION_1_1 = 0;

  public static final int VERSION_1_2 = 1;

  public static final int VERSION_UNKNOWN = 65535;

  public nsIDOMDocument getMessage();

  public void setMessage(nsIDOMDocument arg1);

  public nsIDOMElement getEnvelope();

  public int getVersion();

  public nsIDOMElement getHeader();

  public nsIDOMElement getBody();

  public String getMethodName();

  public String getTargetObjectURI();

  public void encode(int arg1, String arg2, String arg3, long arg4, nsISOAPHeaderBlock[] arg5, long arg6, nsISOAPParameter[] arg7);

  public nsISOAPHeaderBlock[] getHeaderBlocks(long[] arg1);

  public nsISOAPParameter[] getParameters(boolean arg1, long[] arg2);

  public nsISOAPEncoding getEncoding();

  public void setEncoding(nsISOAPEncoding arg1);

  public String getActionURI();

  public void setActionURI(String arg1);

}
