/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIScriptContextOwn">
 **/

package org.mozilla.xpcom;

public interface nsIScriptContextOwner extends nsISupports
{
  public static final String NS_ISCRIPTCONTEXTOWNER_IID =
    "{a94ec640-0bba-11d2-b326-00805f8a3859}";

  public nsISupports getScriptContext();

  public nsISupports getScriptGlobalObject();

  public void releaseScriptContext(nsISupports arg1);

  public void reportScriptError(String arg1, String arg2, int arg3, String arg4);

}
