/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIDebug">
 **/

package org.mozilla.xpcom;

public interface nsIDebug extends nsISupports
{
  public static final String NS_IDEBUG_IID =
    "{3bf0c3d7-3bd9-4cf2-a971-33572c503e1e}";

  public void assertion(String arg1, String arg2, String arg3, int arg4);

  public void warning(String arg1, String arg2, int arg3);

  public void break_(String arg1, int arg2);

  public void abort(String arg1, int arg2);

}
