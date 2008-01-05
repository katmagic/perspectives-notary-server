/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIProcess">
 **/

package org.mozilla.xpcom;

public interface nsIProcess extends nsISupports
{
  public static final String NS_IPROCESS_IID =
    "{9da0b650-d07e-4617-a18a-250035572ac8}";

  public void init(nsIFile arg1);

  public void initWithPid(long arg1);

  public void kill();

  public long run(boolean arg1, String[] arg2, long arg3);

  public nsIFile getLocation();

  public long getPid();

  public String getProcessName();

  public long getProcessSignature();

  public int getExitValue();

}
