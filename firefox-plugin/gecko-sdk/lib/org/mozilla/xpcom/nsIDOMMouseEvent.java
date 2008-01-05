/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIDOMMouseEvent">
 **/

package org.mozilla.xpcom;

public interface nsIDOMMouseEvent extends nsIDOMUIEvent
{
  public static final String NS_IDOMMOUSEEVENT_IID =
    "{ff751edc-8b02-aae7-0010-8301838a3123}";

  public int getScreenX();

  public int getScreenY();

  public int getClientX();

  public int getClientY();

  public boolean getCtrlKey();

  public boolean getShiftKey();

  public boolean getAltKey();

  public boolean getMetaKey();

  public int getButton();

  public nsIDOMEventTarget getRelatedTarget();

  public void initMouseEvent(String arg1, boolean arg2, boolean arg3, nsIDOMAbstractView arg4, int arg5, int arg6, int arg7, int arg8, int arg9, boolean arg10, boolean arg11, boolean arg12, boolean arg13, int arg14, nsIDOMEventTarget arg15);

}
