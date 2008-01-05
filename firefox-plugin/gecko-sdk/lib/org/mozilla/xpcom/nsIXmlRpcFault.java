/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIXmlRpcFault">
 **/

package org.mozilla.xpcom;

public interface nsIXmlRpcFault extends nsISupports
{
  public static final String NS_IXMLRPCFAULT_IID =
    "{691cb864-0a7e-448c-98ee-4a7f359cf145}";

  public int getFaultCode();

  public String getFaultString();

  public void init(int arg1, String arg2);

  public String toString();

}
