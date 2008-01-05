/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIMozIconURI">
 **/

package org.mozilla.xpcom;

public interface nsIMozIconURI extends nsIURI
{
  public static final String NS_IMOZICONURI_IID =
    "{1fb33f44-f522-4880-a225-4b75d09b04c6}";

  public nsIURI getIconFile();

  public void setIconFile(nsIURI arg1);

  public long getImageSize();

  public void setImageSize(long arg1);

  public String getStockIcon();

  public String getIconSize();

  public String getIconState();

  public String getContentType();

  public void setContentType(String arg1);

  public String getFileExtension();

}
