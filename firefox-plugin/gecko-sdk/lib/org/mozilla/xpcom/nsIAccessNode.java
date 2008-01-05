/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIAccessNode">
 **/

package org.mozilla.xpcom;

public interface nsIAccessNode extends nsISupports
{
  public static final String NS_IACCESSNODE_IID =
    "{46820f9b-3088-4046-ab0f-56fdacdc7a82}";

  public nsIDOMNode getDOMNode();

  public int getNumChildren();

  public nsIAccessNode getChildNodeAt(int arg1);

  public nsIAccessNode getParentNode();

  public nsIAccessNode getFirstChildNode();

  public nsIAccessNode getLastChildNode();

  public nsIAccessNode getPreviousSiblingNode();

  public nsIAccessNode getNextSiblingNode();

  public nsIAccessibleDocument getAccessibleDocument();

  public String getInnerHTML();

  public String getComputedStyleValue(String arg1, String arg2);

}
