/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsISelectionListene">
 **/

package org.mozilla.xpcom;

public interface nsISelectionListener extends nsISupports
{
  public static final String NS_ISELECTIONLISTENER_IID =
    "{a6cf90e2-15b3-11d2-932e-00805f8add32}";

  public static final short NO_REASON = 0;

  public static final short DRAG_REASON = 1;

  public static final short MOUSEDOWN_REASON = 2;

  public static final short MOUSEUP_REASON = 4;

  public static final short KEYPRESS_REASON = 8;

  public static final short SELECTALL_REASON = 16;

  public void notifySelectionChanged(nsIDOMDocument arg1, nsISelection arg2, short arg3);

}
