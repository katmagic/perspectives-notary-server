/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsISimpleEnumerator">
 **/

package org.mozilla.xpcom;

public interface nsISimpleEnumerator extends nsISupports
{
  public static final String NS_ISIMPLEENUMERATOR_IID =
    "{d1899240-f9d2-11d2-bdd6-000064657374}";

  public boolean hasMoreElements();

  public nsISupports getNext();

}
