/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIProfileLock">
 **/

package org.mozilla.xpcom;

public interface nsIProfileLock extends nsISupports
{
  public static final String NS_IPROFILELOCK_IID =
    "{50e07b0a-f338-4da3-bcdb-f4bb0db94dbe}";

  public nsILocalFile getDirectory();

  public nsILocalFile getLocalDirectory();

  public void unlock();

}
