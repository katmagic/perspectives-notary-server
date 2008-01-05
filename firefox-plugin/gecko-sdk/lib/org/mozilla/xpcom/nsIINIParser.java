/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIINIParser">
 **/

package org.mozilla.xpcom;

public interface nsIINIParser extends nsISupports
{
  public static final String NS_IINIPARSER_IID =
    "{7eb955f6-3e78-4d39-b72f-c1bf12a94bce}";

  public nsIUTF8StringEnumerator getSections();

  public nsIUTF8StringEnumerator getKeys(String arg1);

  public String getString(String arg1, String arg2);

}
