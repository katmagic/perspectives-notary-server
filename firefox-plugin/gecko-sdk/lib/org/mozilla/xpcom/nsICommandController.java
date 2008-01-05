/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsICommandControlle">
 **/

package org.mozilla.xpcom;

public interface nsICommandController extends nsISupports
{
  public static final String NS_ICOMMANDCONTROLLER_IID =
    "{ebe55080-c8a9-11d5-a73c-dd620d6e04bc}";

  public void getCommandStateWithParams(String arg1, nsICommandParams arg2);

  public void doCommandWithParams(String arg1, nsICommandParams arg2);

}
