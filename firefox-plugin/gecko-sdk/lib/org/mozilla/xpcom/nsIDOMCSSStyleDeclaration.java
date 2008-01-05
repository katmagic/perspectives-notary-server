/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIDOMCSSStyleDecla">
 **/

package org.mozilla.xpcom;

public interface nsIDOMCSSStyleDeclaration extends nsISupports
{
  public static final String NS_IDOMCSSSTYLEDECLARATION_IID =
    "{a6cf90be-15b3-11d2-932e-00805f8add32}";

  public String getCssText();

  public void setCssText(String arg1);

  public String getPropertyValue(String arg1);

  public nsIDOMCSSValue getPropertyCSSValue(String arg1);

  public String removeProperty(String arg1);

  public String getPropertyPriority(String arg1);

  public void setProperty(String arg1, String arg2, String arg3);

  public long getLength();

  public String item(long arg1);

  public nsIDOMCSSRule getParentRule();

}
