/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsISupportsArray">
 **/

package org.mozilla.xpcom;

public interface nsISupportsArray extends nsICollection
{
  public static final String NS_ISUPPORTSARRAY_IID =
    "{791eafa0-b9e6-11d1-8031-006008159b5a}";

  public int getIndexOf(nsISupports arg1);

  public int getIndexOfStartingAt(nsISupports arg1, long arg2);

  public int getLastIndexOf(nsISupports arg1);

  public void deleteLastElement(nsISupports arg1);

  public void deleteElementAt(long arg1);

  public void compact();

  public nsISupportsArray clone_();

}
