/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIPersistentProper">
 **/

package org.mozilla.xpcom;

public interface nsIPersistentProperties extends nsIProperties
{
  public static final String NS_IPERSISTENTPROPERTIES_IID =
    "{1a180f60-93b2-11d2-9b8b-00805f8a16d9}";

  public void load(nsIInputStream arg1);

  public void save(nsIOutputStream arg1, String arg2);

  public void subclass(nsIPersistentProperties arg1);

  public nsISimpleEnumerator enumerate();

  public String getStringProperty(String arg1);

  public String setStringProperty(String arg1, String arg2);

}
