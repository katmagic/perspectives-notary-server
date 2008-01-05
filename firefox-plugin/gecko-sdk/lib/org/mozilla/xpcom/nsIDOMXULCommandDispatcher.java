/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIDOMXULCommandDis">
 **/

package org.mozilla.xpcom;

public interface nsIDOMXULCommandDispatcher extends nsISupports
{
  public static final String NS_IDOMXULCOMMANDDISPATCHER_IID =
    "{f3c50361-14fe-11d3-bf87-00105a1b0627}";

  public nsIDOMElement getFocusedElement();

  public void setFocusedElement(nsIDOMElement arg1);

  public nsIDOMWindow getFocusedWindow();

  public void setFocusedWindow(nsIDOMWindow arg1);

  public void addCommandUpdater(nsIDOMElement arg1, String arg2, String arg3);

  public void removeCommandUpdater(nsIDOMElement arg1);

  public void updateCommands(String arg1);

  public nsIController getControllerForCommand(String arg1);

  public nsIControllers getControllers();

  public void advanceFocus();

  public void rewindFocus();

  public void advanceFocusIntoSubtree(nsIDOMElement arg1);

  public boolean getSuppressFocusScroll();

  public void setSuppressFocusScroll(boolean arg1);

}
