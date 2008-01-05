/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIControllerComman">
 **/

package org.mozilla.xpcom;

public interface nsIControllerCommand extends nsISupports
{
  public static final String NS_ICONTROLLERCOMMAND_IID =
    "{0eae9a46-1dd2-11b2-aca0-9176f05fe9db}";

  public boolean isCommandEnabled(String arg1, nsISupports arg2);

  public void getCommandStateParams(String arg1, nsICommandParams arg2, nsISupports arg3);

  public void doCommand(String arg1, nsISupports arg2);

  public void doCommandParams(String arg1, nsICommandParams arg2, nsISupports arg3);

}
