/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIDOMSVGException">
 **/

package org.mozilla.xpcom;

public interface nsIDOMSVGException extends nsISupports
{
  public static final String NS_IDOMSVGEXCEPTION_IID =
    "{64e6f0e1-af99-4bb9-ab25-7e56012f0021}";

  public static final int SVG_WRONG_TYPE_ERR = 0;

  public static final int SVG_INVALID_VALUE_ERR = 1;

  public static final int SVG_MATRIX_NOT_INVERTABLE = 2;

  public int getCode();

}
