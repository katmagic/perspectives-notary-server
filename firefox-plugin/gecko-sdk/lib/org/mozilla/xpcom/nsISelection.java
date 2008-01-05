/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsISelection">
 **/

package org.mozilla.xpcom;

public interface nsISelection extends nsISupports
{
  public static final String NS_ISELECTION_IID =
    "{b2c7ed59-8634-4352-9e37-5484c8b6e4e1}";

  public nsIDOMNode getAnchorNode();

  public int getAnchorOffset();

  public nsIDOMNode getFocusNode();

  public int getFocusOffset();

  public boolean getIsCollapsed();

  public int getRangeCount();

  public nsIDOMRange getRangeAt(int arg1);

  public void collapse(nsIDOMNode arg1, int arg2);

  public void extend(nsIDOMNode arg1, int arg2);

  public void collapseToStart();

  public void collapseToEnd();

  public boolean containsNode(nsIDOMNode arg1, boolean arg2);

  public void selectAllChildren(nsIDOMNode arg1);

  public void addRange(nsIDOMRange arg1);

  public void removeRange(nsIDOMRange arg1);

  public void removeAllRanges();

  public void deleteFromDocument();

  public void selectionLanguageChange(boolean arg1);

  public String toString();

}
