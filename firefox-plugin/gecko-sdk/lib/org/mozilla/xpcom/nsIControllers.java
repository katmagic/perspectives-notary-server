/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIControllers">
 **/

package org.mozilla.xpcom;

public interface nsIControllers extends nsISupports
{
  public static final String NS_ICONTROLLERS_IID =
    "{a5ed3a01-7cc7-11d3-bf87-00105a1b0627}";

  public nsIDOMXULCommandDispatcher getCommandDispatcher();

  public void setCommandDispatcher(nsIDOMXULCommandDispatcher arg1);

  public nsIController getControllerForCommand(String arg1);

  public void insertControllerAt(long arg1, nsIController arg2);

  public nsIController removeControllerAt(long arg1);

  public nsIController getControllerAt(long arg1);

  public void appendController(nsIController arg1);

  public void removeController(nsIController arg1);

  public long getControllerId(nsIController arg1);

  public nsIController getControllerById(long arg1);

  public long getControllerCount();

}
