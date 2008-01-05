/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIDOMPluginArray">
 **/

package org.mozilla.xpcom;

public interface nsIDOMPluginArray extends nsISupports
{
  public static final String NS_IDOMPLUGINARRAY_IID =
    "{f6134680-f28b-11d2-8360-c90899049c3c}";

  public long getLength();

  public nsIDOMPlugin item(long arg1);

  public nsIDOMPlugin namedItem(String arg1);

}
