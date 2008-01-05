/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIXSLTProcessor">
 **/

package org.mozilla.xpcom;

public interface nsIXSLTProcessor extends nsISupports
{
  public static final String NS_IXSLTPROCESSOR_IID =
    "{4a91aeb3-4100-43ee-a21e-9866268757c5}";

  public void importStylesheet(nsIDOMNode arg1);

  public nsIDOMDocumentFragment transformToFragment(nsIDOMNode arg1, nsIDOMDocument arg2);

  public nsIDOMDocument transformToDocument(nsIDOMNode arg1);

  public void setParameter(String arg1, String arg2, nsIVariant arg3);

  public nsIVariant getParameter(String arg1, String arg2);

  public void removeParameter(String arg1, String arg2);

  public void clearParameters();

  public void reset();

}
