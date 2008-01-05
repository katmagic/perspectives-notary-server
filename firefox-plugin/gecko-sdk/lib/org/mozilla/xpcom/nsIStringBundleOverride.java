/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIStringBundleOver">
 **/

package org.mozilla.xpcom;

public interface nsIStringBundleOverride extends nsISupports
{
  public static final String NS_ISTRINGBUNDLEOVERRIDE_IID =
    "{965eb278-5678-456b-82a7-20a0c86a803c}";

  public String getStringFromName(String arg1, String arg2);

  public nsISimpleEnumerator enumerateKeysInBundle(String arg1);

}
