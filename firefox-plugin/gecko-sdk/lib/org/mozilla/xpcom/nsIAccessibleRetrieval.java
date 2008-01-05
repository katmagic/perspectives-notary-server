/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIAccessibleRetrie">
 **/

package org.mozilla.xpcom;

public interface nsIAccessibleRetrieval extends nsISupports
{
  public static final String NS_IACCESSIBLERETRIEVAL_IID =
    "{663ca4a8-d219-4000-925d-d8f66406b626}";

  public nsIAccessible getAccessibleFor(nsIDOMNode arg1);

  public nsIAccessible getAccessibleInWindow(nsIDOMNode arg1, nsIDOMWindow arg2);

  public nsIAccessible getAccessibleInWeakShell(nsIDOMNode arg1, nsISupports arg2);

  public nsIAccessible getAccessibleInShell(nsIDOMNode arg1, nsISupports arg2);

  public nsIAccessNode getCachedAccessNode(nsIDOMNode arg1, nsISupports arg2);

  public nsIAccessible getCachedAccessible(nsIDOMNode arg1, nsISupports arg2);

}
