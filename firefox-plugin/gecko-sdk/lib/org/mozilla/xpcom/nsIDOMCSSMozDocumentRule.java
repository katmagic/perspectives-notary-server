/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIDOMCSSMozDocumen">
 **/

package org.mozilla.xpcom;

public interface nsIDOMCSSMozDocumentRule extends nsIDOMCSSRule
{
  public static final String NS_IDOMCSSMOZDOCUMENTRULE_IID =
    "{4eb9adac-afaf-4b8a-8640-7340863c1587}";

  public nsIDOMCSSRuleList getCssRules();

  public long insertRule(String arg1, long arg2);

  public void deleteRule(long arg1);

}
