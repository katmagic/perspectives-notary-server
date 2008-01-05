/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIDOMTreeWalker">
 **/

package org.mozilla.xpcom;

public interface nsIDOMTreeWalker extends nsISupports
{
  public static final String NS_IDOMTREEWALKER_IID =
    "{400af3ca-1dd2-11b2-a50a-887ecca2e63a}";

  public nsIDOMNode getRoot();

  public long getWhatToShow();

  public nsIDOMNodeFilter getFilter();

  public boolean getExpandEntityReferences();

  public nsIDOMNode getCurrentNode();

  public void setCurrentNode(nsIDOMNode arg1);

  public nsIDOMNode parentNode();

  public nsIDOMNode firstChild();

  public nsIDOMNode lastChild();

  public nsIDOMNode previousSibling();

  public nsIDOMNode nextSibling();

  public nsIDOMNode previousNode();

  public nsIDOMNode nextNode();

}
