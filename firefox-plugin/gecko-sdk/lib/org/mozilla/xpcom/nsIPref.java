/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIPref">
 **/

package org.mozilla.xpcom;

public interface nsIPref extends nsISupports
{
  public static final String NS_IPREF_IID =
    "{a22ad7b0-ca86-11d1-a9a4-00805f8a7ac4}";

  public static final int ePrefInvalid = 0;

  public static final int ePrefLocked = 1;

  public static final int ePrefUserset = 2;

  public static final int ePrefConfig = 4;

  public static final int ePrefRemote = 8;

  public static final int ePrefLilocal = 16;

  public static final int ePrefString = 32;

  public static final int ePrefInt = 64;

  public static final int ePrefBool = 128;

  public static final int ePrefValuetypeMask = 224;

  public void readUserPrefs(nsIFile arg1);

  public void resetPrefs();

  public void resetUserPrefs();

  public void savePrefFile(nsIFile arg1);

  public nsIPrefBranch getBranch(String arg1);

  public nsIPrefBranch getDefaultBranch(String arg1);

  public String getRoot();

  public int getPrefType(String arg1);

  public boolean getBoolPref(String arg1);

  public void setBoolPref(String arg1, int arg2);

  public String getCharPref(String arg1);

  public void setCharPref(String arg1, String arg2);

  public int getIntPref(String arg1);

  public void setIntPref(String arg1, int arg2);

  public nsISupports getComplexValue(String arg1, String arg2);

  public void setComplexValue(String arg1, String arg2, nsISupports arg3);

  public void clearUserPref(String arg1);

  public boolean prefIsLocked(String arg1);

  public void lockPref(String arg1);

  public void unlockPref(String arg1);

  public void resetBranch(String arg1);

  public void deleteBranch(String arg1);

  public String[] getChildList(String arg1, long[] arg2);

  public void addObserver(String arg1, nsIObserver arg2, boolean arg3);

  public void removeObserver(String arg1, nsIObserver arg2);

  public String copyCharPref(String arg1);

  public String copyDefaultCharPref(String arg1);

  public boolean getDefaultBoolPref(String arg1);

  public int getDefaultIntPref(String arg1);

  public void setDefaultBoolPref(String arg1, boolean arg2);

  public void setDefaultCharPref(String arg1, String arg2);

  public void setDefaultIntPref(String arg1, int arg2);

  public String copyUnicharPref(String arg1);

  public String copyDefaultUnicharPref(String arg1);

  public void setUnicharPref(String arg1, String arg2);

  public void setDefaultUnicharPref(String arg1, String arg2);

  public String getLocalizedUnicharPref(String arg1);

  public String getDefaultLocalizedUnicharPref(String arg1);

  public nsIFileSpec getFilePref(String arg1);

  public void setFilePref(String arg1, nsIFileSpec arg2, boolean arg3);

  public nsILocalFile getFileXPref(String arg1);

  public void setFileXPref(String arg1, nsILocalFile arg2);

}
