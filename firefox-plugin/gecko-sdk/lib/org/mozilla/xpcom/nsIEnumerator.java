/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIEnumerator">
 **/

package org.mozilla.xpcom;

public interface nsIEnumerator extends nsISupports
{
  public static final String NS_IENUMERATOR_IID =
    "{ad385286-cbc4-11d2-8cca-0060b0fc14a3}";

  public void first();

  public void next();

  public nsISupports currentItem();

  public void isDone();

}
