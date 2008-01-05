/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIArray">
 **/

package org.mozilla.xpcom;

public interface nsIArray extends nsISupports
{
  public static final String NS_IARRAY_IID =
    "{114744d9-c369-456e-b55a-52fe52880d2d}";

  public long getLength();

  public nsISupports queryElementAt(long arg1, String arg2);

  public long indexOf(long arg1, nsISupports arg2);

  public nsISimpleEnumerator enumerate();

}
