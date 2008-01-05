/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIDOMCSSStyleRule">
 **/

package org.mozilla.xpcom;

public interface nsIDOMCSSStyleRule extends nsIDOMCSSRule
{
  public static final String NS_IDOMCSSSTYLERULE_IID =
    "{a6cf90bf-15b3-11d2-932e-00805f8add32}";

  public String getSelectorText();

  public void setSelectorText(String arg1);

  public nsIDOMCSSStyleDeclaration getStyle();

}
