/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIDOMDocumentTrave">
 **/

package org.mozilla.xpcom;

public interface nsIDOMDocumentTraversal extends nsISupports
{
  public static final String NS_IDOMDOCUMENTTRAVERSAL_IID =
    "{13f236c0-47f8-11d5-b6a3-009027446e84}";

  public nsIDOMNodeIterator createNodeIterator(nsIDOMNode arg1, long arg2, nsIDOMNodeFilter arg3, boolean arg4);

  public nsIDOMTreeWalker createTreeWalker(nsIDOMNode arg1, long arg2, nsIDOMNodeFilter arg3, boolean arg4);

}
