/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIHttpProtocolHand">
 **/

package org.mozilla.xpcom;

public interface nsIHttpProtocolHandler extends nsIProxiedProtocolHandler
{
  public static final String NS_IHTTPPROTOCOLHANDLER_IID =
    "{122c91c0-2485-40ba-89c9-b895934921bc}";

  public String getUserAgent();

  public String getAppName();

  public String getAppVersion();

  public String getVendor();

  public void setVendor(String arg1);

  public String getVendorSub();

  public void setVendorSub(String arg1);

  public String getVendorComment();

  public void setVendorComment(String arg1);

  public String getProduct();

  public void setProduct(String arg1);

  public String getProductSub();

  public void setProductSub(String arg1);

  public String getProductComment();

  public void setProductComment(String arg1);

  public String getPlatform();

  public String getOscpu();

  public String getLanguage();

  public void setLanguage(String arg1);

  public String getMisc();

  public void setMisc(String arg1);

}
