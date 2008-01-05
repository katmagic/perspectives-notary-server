/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIBidirectionalIte">
 **/

package org.mozilla.xpcom;

public interface nsIBidirectionalIterator extends nsISupports
{
  public static final String NS_IBIDIRECTIONALITERATOR_IID =
    "{948defaa-1dd1-11b2-89f6-8ce81f5ebda9}";

  public nsISupports getElement();

  public void putElement(nsISupports arg1);

  public void stepForward();

  public void stepBackward();

  public boolean isEqualTo(nsISupports arg1);

  public nsISupports clone_();

}
