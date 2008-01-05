/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIDOMCSSMediaRule">
 **/

package org.mozilla.xpcom;

public interface nsIDOMCSSMediaRule extends nsIDOMCSSRule
{
  public static final String NS_IDOMCSSMEDIARULE_IID =
    "{a6cf90bc-15b3-11d2-932e-00805f8add32}";

  public nsIDOMMediaList getMedia();

  public nsIDOMCSSRuleList getCssRules();

  public long insertRule(String arg1, long arg2);

  public void deleteRule(long arg1);

}
