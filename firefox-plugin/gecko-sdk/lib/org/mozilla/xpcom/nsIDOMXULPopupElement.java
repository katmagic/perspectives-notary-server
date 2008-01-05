/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIDOMXULPopupEleme">
 **/

package org.mozilla.xpcom;

public interface nsIDOMXULPopupElement extends nsIDOMXULElement
{
  public static final String NS_IDOMXULPOPUPELEMENT_IID =
    "{c32390a8-2bd8-4d1b-bf9f-1b1d0a944d19}";

  public static final int BEFORE_START = 1;

  public static final int BEFORE_END = 2;

  public static final int AFTER_START = 3;

  public static final int AFTER_END = 4;

  public static final int START_BEFORE = 5;

  public static final int START_AFTER = 6;

  public static final int END_BEFORE = 7;

  public static final int END_AFTER = 8;

  public static final int OVERLAP = 9;

  public static final int AT_POINTER = 10;

  public static final int AFTER_POINTER = 11;

  public String getPosition();

  public void setPosition(String arg1);

  public void showPopup(int arg1, nsIDOMElement arg2, nsIDOMElement arg3);

  public void hidePopup();

}
