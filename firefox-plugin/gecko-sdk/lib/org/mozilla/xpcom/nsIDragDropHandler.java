/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIDragDropHandler">
 **/

package org.mozilla.xpcom;

public interface nsIDragDropHandler extends nsISupports
{
  public static final String NS_IDRAGDROPHANDLER_IID =
    "{4f418f58-f834-4736-a755-e0395bedca9d}";

  public void hookupTo(nsIDOMEventTarget arg1, nsIWebNavigation arg2);

  public void detach();

}
