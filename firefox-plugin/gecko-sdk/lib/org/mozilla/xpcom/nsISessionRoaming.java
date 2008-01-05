/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsISessionRoaming">
 **/

package org.mozilla.xpcom;

public interface nsISessionRoaming extends nsISupports
{
  public static final String NS_ISESSIONROAMING_IID =
    "{ab62465c-494c-446e-b671-930bb98a7bc4}";

  public void beginSession();

  public void endSession();

  public boolean isRoaming();

}
