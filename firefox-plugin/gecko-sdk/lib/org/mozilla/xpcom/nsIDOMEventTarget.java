/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIDOMEventTarget">
 **/

package org.mozilla.xpcom;

public interface nsIDOMEventTarget extends nsISupports
{
  public static final String NS_IDOMEVENTTARGET_IID =
    "{1c773b30-d1cf-11d2-bd95-00805f8ae3f4}";

  public void addEventListener(String arg1, nsIDOMEventListener arg2, boolean arg3);

  public void removeEventListener(String arg1, nsIDOMEventListener arg2, boolean arg3);

  public boolean dispatchEvent(nsIDOMEvent arg1);

}
