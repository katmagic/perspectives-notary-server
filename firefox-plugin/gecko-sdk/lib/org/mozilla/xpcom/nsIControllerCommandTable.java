/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIControllerComman">
 **/

package org.mozilla.xpcom;

public interface nsIControllerCommandTable extends nsISupports
{
  public static final String NS_ICONTROLLERCOMMANDTABLE_IID =
    "{d1a47834-6ad4-11d7-bfad-000393636592}";

  public void makeImmutable();

  public void registerCommand(String arg1, nsIControllerCommand arg2);

  public void unregisterCommand(String arg1, nsIControllerCommand arg2);

  public nsIControllerCommand findCommandHandler(String arg1);

  public boolean isCommandEnabled(String arg1, nsISupports arg2);

  public void updateCommandState(String arg1, nsISupports arg2);

  public boolean supportsCommand(String arg1, nsISupports arg2);

  public void doCommand(String arg1, nsISupports arg2);

  public void doCommandParams(String arg1, nsICommandParams arg2, nsISupports arg3);

  public void getCommandState(String arg1, nsICommandParams arg2, nsISupports arg3);

}
