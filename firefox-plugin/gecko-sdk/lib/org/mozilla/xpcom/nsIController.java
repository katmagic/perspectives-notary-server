/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIController">
 **/

package org.mozilla.xpcom;

public interface nsIController extends nsISupports
{
  public static final String NS_ICONTROLLER_IID =
    "{d5b61b82-1da4-11d3-bf87-00105a1b0627}";

  public boolean isCommandEnabled(String arg1);

  public boolean supportsCommand(String arg1);

  public void doCommand(String arg1);

  public void onEvent(String arg1);

}
