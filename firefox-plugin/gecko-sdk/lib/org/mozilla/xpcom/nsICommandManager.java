/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsICommandManager">
 **/

package org.mozilla.xpcom;

public interface nsICommandManager extends nsISupports
{
  public static final String NS_ICOMMANDMANAGER_IID =
    "{080d2001-f91e-11d4-a73c-f9242928207c}";

  public void addCommandObserver(nsIObserver arg1, String arg2);

  public void removeCommandObserver(nsIObserver arg1, String arg2);

  public boolean isCommandSupported(String arg1, nsIDOMWindow arg2);

  public boolean isCommandEnabled(String arg1, nsIDOMWindow arg2);

  public void getCommandState(String arg1, nsIDOMWindow arg2, nsICommandParams arg3);

  public void doCommand(String arg1, nsICommandParams arg2, nsIDOMWindow arg3);

}
