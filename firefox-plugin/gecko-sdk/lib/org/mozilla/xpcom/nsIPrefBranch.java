/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIPrefBranch">
 **/

package org.mozilla.xpcom;

public interface nsIPrefBranch extends nsISupports
{
  public static final String NS_IPREFBRANCH_IID =
    "{56c35506-f14b-11d3-99d3-ddbfac2ccf65}";

  public static final int PREF_INVALID = 0;

  public static final int PREF_STRING = 32;

  public static final int PREF_INT = 64;

  public static final int PREF_BOOL = 128;

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

  public void lockPref(String arg1);

  public boolean prefHasUserValue(String arg1);

  public boolean prefIsLocked(String arg1);

  public void unlockPref(String arg1);

  public void deleteBranch(String arg1);

  public String[] getChildList(String arg1, long[] arg2);

  public void resetBranch(String arg1);

}
