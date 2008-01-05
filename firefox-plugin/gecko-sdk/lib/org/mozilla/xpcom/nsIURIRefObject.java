/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIURIRefObject">
 **/

package org.mozilla.xpcom;

public interface nsIURIRefObject extends nsISupports
{
  public static final String NS_IURIREFOBJECT_IID =
    "{2226927e-1dd2-11b2-b57f-faab47288563}";

  public nsIDOMNode getNode();

  public void setNode(nsIDOMNode arg1);

  public void reset();

  public String getNextURI();

  public void rewriteAllURIs(String arg1, String arg2, boolean arg3);

}
