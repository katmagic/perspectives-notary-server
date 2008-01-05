/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIDOMNavigator">
 **/

package org.mozilla.xpcom;

public interface nsIDOMNavigator extends nsISupports
{
  public static final String NS_IDOMNAVIGATOR_IID =
    "{8758b72b-63d4-4685-b908-4275126410fb}";

  public String getAppCodeName();

  public String getAppName();

  public String getAppVersion();

  public String getLanguage();

  public nsIDOMMimeTypeArray getMimeTypes();

  public String getPlatform();

  public String getOscpu();

  public String getVendor();

  public String getVendorSub();

  public String getProduct();

  public String getProductSub();

  public nsIDOMPluginArray getPlugins();

  public String getSecurityPolicy();

  public String getUserAgent();

  public boolean getCookieEnabled();

  public boolean getOnLine();

  public boolean javaEnabled();

  public boolean taintEnabled();

}
