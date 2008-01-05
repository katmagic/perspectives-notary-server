/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIDOMXPathEvaluato">
 **/

package org.mozilla.xpcom;

public interface nsIDOMXPathEvaluator extends nsISupports
{
  public static final String NS_IDOMXPATHEVALUATOR_IID =
    "{75506f8a-b504-11d5-a7f2-ca108ab8b6fc}";

  public nsIDOMXPathExpression createExpression(String arg1, nsIDOMXPathNSResolver arg2);

  public nsIDOMXPathNSResolver createNSResolver(nsIDOMNode arg1);

  public nsISupports evaluate(String arg1, nsIDOMNode arg2, nsIDOMXPathNSResolver arg3, int arg4, nsISupports arg5);

}
