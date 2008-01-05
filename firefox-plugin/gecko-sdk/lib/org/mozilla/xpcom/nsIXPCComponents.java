/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIXPCComponents">
 **/

package org.mozilla.xpcom;

public interface nsIXPCComponents extends nsISupports
{
  public static final String NS_IXPCCOMPONENTS_IID =
    "{155809f1-71f1-47c5-be97-d812ba560405}";

  public nsIScriptableInterfaces getInterfaces();

  public nsIScriptableInterfacesByID getInterfacesByID();

  public nsIXPCComponents_Classes getClasses();

  public nsIXPCComponents_ClassesByID getClassesByID();

  public nsIStackFrame getStack();

  public nsIXPCComponents_Results getResults();

  public nsIComponentManager getManager();

  public nsIXPCComponents_Utils getUtils();

  public nsIXPCComponents_ID getID();

  public nsIXPCComponents_Exception getException();

  public nsIXPCComponents_Constructor getConstructor();

  public boolean isSuccessCode(long arg1);

  public void lookupMethod();

  public void reportError();

}
