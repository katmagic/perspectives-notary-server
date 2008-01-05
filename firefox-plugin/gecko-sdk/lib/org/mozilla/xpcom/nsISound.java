/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsISound">
 **/

package org.mozilla.xpcom;

public interface nsISound extends nsISupports
{
  public static final String NS_ISOUND_IID =
    "{b148eed1-236d-11d3-b35c-00a0cc3c1cde}";

  public void play(nsIURL arg1);

  public void playSystemSound(String arg1);

  public void beep();

  public void init();

}
