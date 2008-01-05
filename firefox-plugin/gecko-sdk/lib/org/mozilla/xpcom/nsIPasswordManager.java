/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIPasswordManager">
 **/

package org.mozilla.xpcom;

public interface nsIPasswordManager extends nsISupports
{
  public static final String NS_IPASSWORDMANAGER_IID =
    "{173562f0-2173-11d5-a54c-0010a401eb10}";

  public void addUser(String arg1, String arg2, String arg3);

  public void removeUser(String arg1, String arg2);

  public void addReject(String arg1);

  public void removeReject(String arg1);

  public nsISimpleEnumerator getEnumerator();

  public nsISimpleEnumerator getRejectEnumerator();

}
