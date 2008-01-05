/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIToolkitProfile">
 **/

package org.mozilla.xpcom;

public interface nsIToolkitProfile extends nsISupports
{
  public static final String NS_ITOOLKITPROFILE_IID =
    "{7422b090-4a86-4407-972e-75468a625388}";

  public nsILocalFile getRootDir();

  public nsILocalFile getLocalDir();

  public String getName();

  public void setName(String arg1);

  public void remove(boolean arg1);

  public nsIProfileLock lock(nsIProfileUnlocker[] arg1);

}
