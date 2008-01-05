/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIStringBundle">
 **/

package org.mozilla.xpcom;

public interface nsIStringBundle extends nsISupports
{
  public static final String NS_ISTRINGBUNDLE_IID =
    "{d85a17c2-aa7c-11d2-9b8c-00805f8a16d9}";

  public String getStringFromID(int arg1);

  public String getStringFromName(String arg1);

  public String formatStringFromID(int arg1, String[] arg2, long arg3);

  public String formatStringFromName(String arg1, String[] arg2, long arg3);

  public nsISimpleEnumerator getSimpleEnumeration();

}
