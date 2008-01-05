/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIXULRuntime">
 **/

package org.mozilla.xpcom;

public interface nsIXULRuntime extends nsISupports
{
  public static final String NS_IXULRUNTIME_IID =
    "{2848ab92-d912-11d9-89f7-001124787b2e}";

  public boolean getInSafeMode();

  public boolean getLogConsoleErrors();

  public void setLogConsoleErrors(boolean arg1);

  public String getOS();

  public String getXPCOMABI();

}
