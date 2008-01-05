/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIStringEnumerator">
 **/

package org.mozilla.xpcom;

public interface nsIStringEnumerator extends nsISupports
{
  public static final String NS_ISTRINGENUMERATOR_IID =
    "{50d3ef6c-9380-4f06-9fb2-95488f7d141c}";

  public boolean hasMore();

  public String getNext();

}
