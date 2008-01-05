/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIPrintStatusFeedb">
 **/

package org.mozilla.xpcom;

public interface nsIPrintStatusFeedback extends nsISupports
{
  public static final String NS_IPRINTSTATUSFEEDBACK_IID =
    "{19855dff-3248-4902-b196-93ee4c477880}";

  public void showStatusString(String arg1);

  public void startMeteors();

  public void stopMeteors();

  public void showProgress(int arg1);

  public void closeWindow();

}
