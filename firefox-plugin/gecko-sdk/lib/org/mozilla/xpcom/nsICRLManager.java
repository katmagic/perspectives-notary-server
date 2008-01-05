/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsICRLManager">
 **/

package org.mozilla.xpcom;

public interface nsICRLManager extends nsISupports
{
  public static final String NS_ICRLMANAGER_IID =
    "{486755db-627a-4678-a21b-f6a63bb9c56a}";

  public static final long TYPE_AUTOUPDATE_TIME_BASED = 1L;

  public static final long TYPE_AUTOUPDATE_FREQ_BASED = 2L;

  public void importCrl(short[] arg1, long arg2, nsIURI arg3, long arg4, boolean arg5, String arg6);

  public boolean updateCRLFromURL(String arg1, String arg2);

  public nsIArray getCrls();

  public void deleteCrl(long arg1);

  public void rescheduleCRLAutoUpdate();

  public String computeNextAutoUpdateTime(nsICRLInfo arg1, long arg2, double arg3);

}
