/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIDOMNSRange">
 **/

package org.mozilla.xpcom;

public interface nsIDOMNSRange extends nsISupports
{
  public static final String NS_IDOMNSRANGE_IID =
    "{a6cf90f2-15b3-11d2-932e-00805f8add32}";

  public static final int NODE_BEFORE = 0;

  public static final int NODE_AFTER = 1;

  public static final int NODE_BEFORE_AND_AFTER = 2;

  public static final int NODE_INSIDE = 3;

  public nsIDOMDocumentFragment createContextualFragment(String arg1);

  public boolean isPointInRange(nsIDOMNode arg1, int arg2);

  public short comparePoint(nsIDOMNode arg1, int arg2);

  public boolean intersectsNode(nsIDOMNode arg1);

  public int compareNode(nsIDOMNode arg1);

  public void nSDetach();

}
