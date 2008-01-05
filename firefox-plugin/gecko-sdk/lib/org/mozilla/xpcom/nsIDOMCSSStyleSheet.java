/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIDOMCSSStyleSheet">
 **/

package org.mozilla.xpcom;

public interface nsIDOMCSSStyleSheet extends nsIDOMStyleSheet
{
  public static final String NS_IDOMCSSSTYLESHEET_IID =
    "{a6cf90c2-15b3-11d2-932e-00805f8add32}";

  public nsIDOMCSSRule getOwnerRule();

  public nsIDOMCSSRuleList getCssRules();

  public long insertRule(String arg1, long arg2);

  public void deleteRule(long arg1);

}
