/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIDOMHTMLOptionsCo">
 **/

package org.mozilla.xpcom;

public interface nsIDOMHTMLOptionsCollection extends nsISupports
{
  public static final String NS_IDOMHTMLOPTIONSCOLLECTION_IID =
    "{bce0213c-f70f-488f-b93f-688acca55d63}";

  public long getLength();

  public void setLength(long arg1);

  public nsIDOMNode item(long arg1);

  public nsIDOMNode namedItem(String arg1);

}
