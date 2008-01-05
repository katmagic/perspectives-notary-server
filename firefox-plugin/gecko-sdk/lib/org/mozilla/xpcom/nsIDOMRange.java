/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIDOMRange">
 **/

package org.mozilla.xpcom;

public interface nsIDOMRange extends nsISupports
{
  public static final String NS_IDOMRANGE_IID =
    "{a6cf90ce-15b3-11d2-932e-00805f8add32}";

  public static final int START_TO_START = 0;

  public static final int START_TO_END = 1;

  public static final int END_TO_END = 2;

  public static final int END_TO_START = 3;

  public nsIDOMNode getStartContainer();

  public int getStartOffset();

  public nsIDOMNode getEndContainer();

  public int getEndOffset();

  public boolean getCollapsed();

  public nsIDOMNode getCommonAncestorContainer();

  public void setStart(nsIDOMNode arg1, int arg2);

  public void setEnd(nsIDOMNode arg1, int arg2);

  public void setStartBefore(nsIDOMNode arg1);

  public void setStartAfter(nsIDOMNode arg1);

  public void setEndBefore(nsIDOMNode arg1);

  public void setEndAfter(nsIDOMNode arg1);

  public void collapse(boolean arg1);

  public void selectNode(nsIDOMNode arg1);

  public void selectNodeContents(nsIDOMNode arg1);

  public short compareBoundaryPoints(int arg1, nsIDOMRange arg2);

  public void deleteContents();

  public nsIDOMDocumentFragment extractContents();

  public nsIDOMDocumentFragment cloneContents();

  public void insertNode(nsIDOMNode arg1);

  public void surroundContents(nsIDOMNode arg1);

  public nsIDOMRange cloneRange();

  public String toString();

  public void detach();

}
