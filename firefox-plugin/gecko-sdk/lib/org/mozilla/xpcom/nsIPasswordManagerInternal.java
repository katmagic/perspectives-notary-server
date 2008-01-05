/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIPasswordManagerI">
 **/

package org.mozilla.xpcom;

public interface nsIPasswordManagerInternal extends nsISupports
{
  public static final String NS_IPASSWORDMANAGERINTERNAL_IID =
    "{dc2ff152-85cb-474e-b4c2-86a3d48cf4d0}";

  public void findPasswordEntry(String arg1, String arg2, String arg3, String arg4, String arg5, String arg6);

  public void addUserFull(String arg1, String arg2, String arg3, String arg4, String arg5);

  public void readPasswords(nsIFile arg1);

}
