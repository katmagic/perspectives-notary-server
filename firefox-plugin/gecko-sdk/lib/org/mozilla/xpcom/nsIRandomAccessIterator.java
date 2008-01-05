/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIRandomAccessIter">
 **/

package org.mozilla.xpcom;

public interface nsIRandomAccessIterator extends nsISupports
{
  public static final String NS_IRANDOMACCESSITERATOR_IID =
    "{9bd6fdb0-1dd1-11b2-9101-d15375968230}";

  public nsISupports getElement();

  public nsISupports getElementAt(int arg1);

  public void putElement(nsISupports arg1);

  public void putElementAt(int arg1, nsISupports arg2);

  public void stepForward();

  public void stepForwardBy(int arg1);

  public void stepBackward();

  public void stepBackwardBy(int arg1);

  public boolean isEqualTo(nsISupports arg1);

  public nsISupports clone_();

}
