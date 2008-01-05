/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIDictionary">
 **/

package org.mozilla.xpcom;

public interface nsIDictionary extends nsISupports
{
  public static final String NS_IDICTIONARY_IID =
    "{1dd0cb45-aea3-4a52-8b29-01429a542863}";

  public boolean hasKey(String arg1);

  public String[] getKeys(long[] arg1);

  public nsISupports getValue(String arg1);

  public void setValue(String arg1, nsISupports arg2);

  public nsISupports deleteValue(String arg1);

  public void clear();

}
