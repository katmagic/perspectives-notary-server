/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIHTTPIndex">
 **/

package org.mozilla.xpcom;

public interface nsIHTTPIndex extends nsISupports
{
  public static final String NS_IHTTPINDEX_IID =
    "{6f2bdbd0-58c3-11d3-be36-00104bde6048}";

  public String getBaseURL();

  public nsIRDFDataSource getDataSource();

  public String getEncoding();

  public void setEncoding(String arg1);

}
