/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIDOMCSSRule">
 **/

package org.mozilla.xpcom;

public interface nsIDOMCSSRule extends nsISupports
{
  public static final String NS_IDOMCSSRULE_IID =
    "{a6cf90c1-15b3-11d2-932e-00805f8add32}";

  public static final int UNKNOWN_RULE = 0;

  public static final int STYLE_RULE = 1;

  public static final int CHARSET_RULE = 2;

  public static final int IMPORT_RULE = 3;

  public static final int MEDIA_RULE = 4;

  public static final int FONT_FACE_RULE = 5;

  public static final int PAGE_RULE = 6;

  public int getType();

  public String getCssText();

  public void setCssText(String arg1);

  public nsIDOMCSSStyleSheet getParentStyleSheet();

  public nsIDOMCSSRule getParentRule();

}
