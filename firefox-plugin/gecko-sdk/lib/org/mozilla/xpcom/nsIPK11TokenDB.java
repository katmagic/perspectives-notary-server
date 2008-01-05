/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIPK11TokenDB">
 **/

package org.mozilla.xpcom;

public interface nsIPK11TokenDB extends nsISupports
{
  public static final String NS_IPK11TOKENDB_IID =
    "{4ee28c82-1dd2-11b2-aabf-bb4017abe395}";

  public nsIPK11Token getInternalKeyToken();

  public nsIPK11Token findTokenByName(String arg1);

  public nsIEnumerator listTokens();

}
