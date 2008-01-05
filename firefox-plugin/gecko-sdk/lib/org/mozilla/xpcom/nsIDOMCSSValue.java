/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIDOMCSSValue">
 **/

package org.mozilla.xpcom;

public interface nsIDOMCSSValue extends nsISupports
{
  public static final String NS_IDOMCSSVALUE_IID =
    "{009f7ea5-9e80-41be-b008-db62f10823f2}";

  public static final int CSS_INHERIT = 0;

  public static final int CSS_PRIMITIVE_VALUE = 1;

  public static final int CSS_VALUE_LIST = 2;

  public static final int CSS_CUSTOM = 3;

  public String getCssText();

  public void setCssText(String arg1);

  public int getCssValueType();

}
