/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIDOMUIEvent">
 **/

package org.mozilla.xpcom;

public interface nsIDOMUIEvent extends nsIDOMEvent
{
  public static final String NS_IDOMUIEVENT_IID =
    "{a6cf90c3-15b3-11d2-932e-00805f8add32}";

  public nsIDOMAbstractView getView();

  public int getDetail();

  public void initUIEvent(String arg1, boolean arg2, boolean arg3, nsIDOMAbstractView arg4, int arg5);

}
