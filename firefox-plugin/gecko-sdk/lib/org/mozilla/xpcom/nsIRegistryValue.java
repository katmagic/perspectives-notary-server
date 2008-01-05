/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIRegistryValue">
 **/

package org.mozilla.xpcom;

public interface nsIRegistryValue extends nsISupports
{
  public static final String NS_IREGISTRYVALUE_IID =
    "{5316c380-b2f8-11d2-a374-0080c6f80e4b}";

  public String getName();

  public String getNameUTF8();

  public long getType();

  public long getLength();

}
