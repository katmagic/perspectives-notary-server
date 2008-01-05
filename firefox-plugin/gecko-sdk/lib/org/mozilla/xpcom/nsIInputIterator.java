/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIInputIterator">
 **/

package org.mozilla.xpcom;

public interface nsIInputIterator extends nsISupports
{
  public static final String NS_IINPUTITERATOR_IID =
    "{85585e12-1dd2-11b2-a930-f6929058269a}";

  public nsISupports getElement();

  public void stepForward();

  public boolean isEqualTo(nsISupports arg1);

  public nsISupports clone_();

}
