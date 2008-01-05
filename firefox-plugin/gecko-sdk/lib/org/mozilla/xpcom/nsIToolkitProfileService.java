/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIToolkitProfileSe">
 **/

package org.mozilla.xpcom;

public interface nsIToolkitProfileService extends nsISupports
{
  public static final String NS_ITOOLKITPROFILESERVICE_IID =
    "{9b434f48-438c-4f85-89de-b7f321a45341}";

  public boolean getStartWithLastProfile();

  public void setStartWithLastProfile(boolean arg1);

  public boolean getStartOffline();

  public void setStartOffline(boolean arg1);

  public nsISimpleEnumerator getProfiles();

  public nsIToolkitProfile getSelectedProfile();

  public void setSelectedProfile(nsIToolkitProfile arg1);

  public nsIToolkitProfile getProfileByName(String arg1);

  public nsIProfileLock lockProfilePath(nsILocalFile arg1, nsILocalFile arg2);

  public nsIToolkitProfile createProfile(nsILocalFile arg1, nsILocalFile arg2, String arg3);

  public long getProfileCount();

  public void flush();

}
