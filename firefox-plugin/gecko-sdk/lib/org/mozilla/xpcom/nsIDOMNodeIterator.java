/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIDOMNodeIterator">
 **/

package org.mozilla.xpcom;

public interface nsIDOMNodeIterator extends nsISupports
{
  public static final String NS_IDOMNODEITERATOR_IID =
    "{354b5f02-1dd2-11b2-b053-b8c2997022a0}";

  public nsIDOMNode getRoot();

  public long getWhatToShow();

  public nsIDOMNodeFilter getFilter();

  public boolean getExpandEntityReferences();

  public nsIDOMNode nextNode();

  public nsIDOMNode previousNode();

  public void detach();

}
