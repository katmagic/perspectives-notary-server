/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIBrowserInstance">
 **/

package org.mozilla.xpcom;

public interface nsIBrowserInstance extends nsISupports
{
  public static final String NS_IBROWSERINSTANCE_IID =
    "{8af0fa40-598d-11d3-806a-00600811a9c3}";

  public boolean startPageCycler();

  public boolean getCmdLineURLUsed();

  public void setCmdLineURLUsed(boolean arg1);

  public void setWebShellWindow(nsIDOMWindowInternal arg1);

  public void close();

}
