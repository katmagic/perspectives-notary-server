/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsILocaleService">
 **/

package org.mozilla.xpcom;

public interface nsILocaleService extends nsISupports
{
  public static final String NS_ILOCALESERVICE_IID =
    "{48ab1fa0-4550-11d3-91cd-00105aa3f7dc}";

  public nsILocale newLocale(String arg1);

  public nsILocale newLocaleObject(nsILocaleDefinition arg1);

  public nsILocale getSystemLocale();

  public nsILocale getApplicationLocale();

  public nsILocale getLocaleFromAcceptLanguage(String arg1);

  public String getLocaleComponentForUserAgent();

}
