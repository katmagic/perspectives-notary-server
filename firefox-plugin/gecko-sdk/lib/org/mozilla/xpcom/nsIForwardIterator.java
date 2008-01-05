/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIForwardIterator">
 **/

package org.mozilla.xpcom;

public interface nsIForwardIterator extends nsISupports
{
  public static final String NS_IFORWARDITERATOR_IID =
    "{8da01646-1dd2-11b2-98a7-c7009045be7e}";

  public nsISupports getElement();

  public void putElement(nsISupports arg1);

  public void stepForward();

  public boolean isEqualTo(nsISupports arg1);

  public nsISupports clone_();

}
