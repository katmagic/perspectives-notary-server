/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsICollection">
 **/

package org.mozilla.xpcom;

public interface nsICollection extends nsISerializable
{
  public static final String NS_ICOLLECTION_IID =
    "{83b6019c-cbc4-11d2-8cca-0060b0fc14a3}";

  public long count();

  public nsISupports getElementAt(long arg1);

  public nsISupports queryElementAt(long arg1, String arg2);

  public void setElementAt(long arg1, nsISupports arg2);

  public void appendElement(nsISupports arg1);

  public void removeElement(nsISupports arg1);

  public nsIEnumerator enumerate();

  public void clear();

}
