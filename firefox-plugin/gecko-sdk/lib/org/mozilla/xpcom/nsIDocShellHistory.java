/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIDocShellHistory">
 **/

package org.mozilla.xpcom;

public interface nsIDocShellHistory extends nsISupports
{
  public static final String NS_IDOCSHELLHISTORY_IID =
    "{89caa9f0-8b1c-47fb-b0d3-f0aef0bff749}";

  public nsISHEntry getChildSHEntry(int arg1);

  public void addChildSHEntry(nsISHEntry arg1, nsISHEntry arg2, int arg3);

  public boolean getUseGlobalHistory();

  public void setUseGlobalHistory(boolean arg1);

}
