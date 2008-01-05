/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIPopupBoxObject">
 **/

package org.mozilla.xpcom;

public interface nsIPopupBoxObject extends nsISupports
{
  public static final String NS_IPOPUPBOXOBJECT_IID =
    "{33c60e14-5150-4876-9a96-2732557e6895}";

  public void showPopup(nsIDOMElement arg1, nsIDOMElement arg2, int arg3, int arg4, String arg5, String arg6, String arg7);

  public void hidePopup();

  public boolean getAutoPosition();

  public void setAutoPosition(boolean arg1);

  public void enableKeyboardNavigator(boolean arg1);

  public void enableRollup(boolean arg1);

  public void sizeTo(int arg1, int arg2);

  public void moveTo(int arg1, int arg2);

}
