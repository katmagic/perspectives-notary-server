/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIDOMHTMLCollectio">
 **/

package org.mozilla.xpcom;

public interface nsIDOMHTMLCollection extends nsISupports
{
  public static final String NS_IDOMHTMLCOLLECTION_IID =
    "{a6cf9083-15b3-11d2-932e-00805f8add32}";

  public long getLength();

  public nsIDOMNode item(long arg1);

  public nsIDOMNode namedItem(String arg1);

}
