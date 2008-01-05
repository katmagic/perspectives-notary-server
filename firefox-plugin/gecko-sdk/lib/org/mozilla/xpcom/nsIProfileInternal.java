/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIProfileInternal">
 **/

package org.mozilla.xpcom;

public interface nsIProfileInternal extends nsIProfile
{
  public static final String NS_IPROFILEINTERNAL_IID =
    "{2f977d42-5485-11d4-87e2-0010a4e75ef2}";

  public static final long LIST_ONLY_NEW = 1L;

  public static final long LIST_ONLY_OLD = 2L;

  public static final long LIST_ALL = 3L;

  public static final long LIST_FOR_IMPORT = 4L;

  public int get4xProfileCount();

  public String[] getProfileListX(long arg1, long[] arg2);

  public void migrateProfileInfo();

  public void migrateAllProfiles();

  public void migrateProfile(String arg1);

  public void remigrateProfile(String arg1);

  public void forgetCurrentProfile();

  public void createDefaultProfile();

  public nsIFile getProfileDir(String arg1);

  public String getProfilePath(String arg1);

  public nsILocalFile getOriginalProfileDir(String arg1);

  public long getProfileLastModTime(String arg1);

  public boolean getAutomigrate();

  public void setAutomigrate(boolean arg1);

  public nsIFile getDefaultProfileParentDir();

  public String getFirstProfile();

  public boolean getStartWithLastUsedProfile();

  public void setStartWithLastUsedProfile(boolean arg1);

  public void createNewProfileWithLocales(String arg1, String arg2, String arg3, String arg4, boolean arg5);

  public boolean isCurrentProfileAvailable();

}
