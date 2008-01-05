/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIProfile">
 **/

package org.mozilla.xpcom;

public interface nsIProfile extends nsISupports
{
  public static final String NS_IPROFILE_IID =
    "{02b0625a-e7f3-11d2-9f5a-006008a6efe9}";

  public static final long SHUTDOWN_PERSIST = 1L;

  public static final long SHUTDOWN_CLEANSE = 2L;

  public int getProfileCount();

  public String[] getProfileList(long[] arg1);

  public boolean profileExists(String arg1);

  public String getCurrentProfile();

  public void setCurrentProfile(String arg1);

  public void shutDownCurrentProfile(long arg1);

  public void createNewProfile(String arg1, String arg2, String arg3, boolean arg4);

  public void renameProfile(String arg1, String arg2);

  public void deleteProfile(String arg1, boolean arg2);

  public void cloneProfile(String arg1);

}
