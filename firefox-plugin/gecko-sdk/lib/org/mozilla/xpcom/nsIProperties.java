/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIProperties">
 **/

package org.mozilla.xpcom;

public interface nsIProperties extends nsISupports
{
  public static final String NS_IPROPERTIES_IID =
    "{78650582-4e93-4b60-8e85-26ebd3eb14ca}";

  public nsISupports get(String arg1, String arg2);

  public void set(String arg1, nsISupports arg2);

  public boolean has(String arg1);

  public void undefine(String arg1);

  public String[] getKeys(long[] arg1);

}
