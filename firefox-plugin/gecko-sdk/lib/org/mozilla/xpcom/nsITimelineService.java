/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsITimelineService">
 **/

package org.mozilla.xpcom;

public interface nsITimelineService extends nsISupports
{
  public static final String NS_ITIMELINESERVICE_IID =
    "{93276790-3daf-11d5-b67d-000064657374}";

  public void mark(String arg1);

  public void indent();

  public void outdent();

  public void enter(String arg1);

  public void leave(String arg1);

  public void startTimer(String arg1);

  public void stopTimer(String arg1);

  public void markTimer(String arg1);

  public void resetTimer(String arg1);

  public void markTimerWithComment(String arg1, String arg2);

}
