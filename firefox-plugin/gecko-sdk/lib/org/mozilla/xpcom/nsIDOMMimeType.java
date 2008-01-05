/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIDOMMimeType">
 **/

package org.mozilla.xpcom;

public interface nsIDOMMimeType extends nsISupports
{
  public static final String NS_IDOMMIMETYPE_IID =
    "{f6134682-f28b-11d2-8360-c90899049c3c}";

  public String getDescription();

  public nsIDOMPlugin getEnabledPlugin();

  public String getSuffixes();

  public String getType();

}
