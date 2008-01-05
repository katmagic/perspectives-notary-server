/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIStyleSheetServic">
 **/

package org.mozilla.xpcom;

public interface nsIStyleSheetService extends nsISupports
{
  public static final String NS_ISTYLESHEETSERVICE_IID =
    "{41d979dc-ea03-4235-86ff-1e3c090c5630}";

  public static final long AGENT_SHEET = 0L;

  public static final long USER_SHEET = 1L;

  public void loadAndRegisterSheet(nsIURI arg1, long arg2);

  public boolean sheetRegistered(nsIURI arg1, long arg2);

  public void unregisterSheet(nsIURI arg1, long arg2);

}
