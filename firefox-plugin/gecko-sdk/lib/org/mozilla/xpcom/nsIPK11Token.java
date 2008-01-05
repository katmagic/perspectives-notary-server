/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIPK11Token">
 **/

package org.mozilla.xpcom;

public interface nsIPK11Token extends nsISupports
{
  public static final String NS_IPK11TOKEN_IID =
    "{51191434-1dd2-11b2-a17c-e49c4e99a4e3}";

  public static final int ASK_EVERY_TIME = -1;

  public static final int ASK_FIRST_TIME = 0;

  public static final int ASK_EXPIRE_TIME = 1;

  public String getTokenName();

  public String getTokenLabel();

  public String getTokenManID();

  public String getTokenHWVersion();

  public String getTokenFWVersion();

  public String getTokenSerialNumber();

  public boolean isLoggedIn();

  public void login(boolean arg1);

  public void logoutSimple();

  public void logoutAndDropAuthenticatedResources();

  public void reset();

  public int getMinimumPasswordLength();

  public boolean getNeedsUserInit();

  public boolean checkPassword(String arg1);

  public void initPassword(String arg1);

  public void changePassword(String arg1, String arg2);

  public int getAskPasswordTimes();

  public int getAskPasswordTimeout();

  public void setAskPasswordDefaults(int arg1, int arg2);

  public boolean isHardwareToken();

  public boolean needsLogin();

  public boolean isFriendly();

}
