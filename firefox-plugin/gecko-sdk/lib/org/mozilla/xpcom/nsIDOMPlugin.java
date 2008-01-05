/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIDOMPlugin">
 **/

package org.mozilla.xpcom;

public interface nsIDOMPlugin extends nsISupports
{
  public static final String NS_IDOMPLUGIN_IID =
    "{f6134681-f28b-11d2-8360-c90899049c3c}";

  public String getDescription();

  public String getFilename();

  public String getName();

  public long getLength();

  public nsIDOMMimeType item(long arg1);

  public nsIDOMMimeType namedItem(String arg1);

}
