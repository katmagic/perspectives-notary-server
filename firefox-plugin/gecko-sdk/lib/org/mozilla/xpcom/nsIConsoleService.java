/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIConsoleService">
 **/

package org.mozilla.xpcom;

public interface nsIConsoleService extends nsISupports
{
  public static final String NS_ICONSOLESERVICE_IID =
    "{a647f184-1dd1-11b2-a9d1-8537b201161b}";

  public void logMessage(nsIConsoleMessage arg1);

  public void logStringMessage(String arg1);

  public void getMessageArray(nsIConsoleMessage[][] arg1, long[] arg2);

  public void registerListener(nsIConsoleListener arg1);

  public void unregisterListener(nsIConsoleListener arg1);

}
