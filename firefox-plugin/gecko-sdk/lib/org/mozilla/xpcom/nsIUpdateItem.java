/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIUpdateItem">
 **/

package org.mozilla.xpcom;

public interface nsIUpdateItem extends nsISupports
{
  public static final String NS_IUPDATEITEM_IID =
    "{7f952767-427f-402b-8114-f80c95d1980d}";

  public static final long TYPE_APP = 1L;

  public static final long TYPE_EXTENSION = 2L;

  public static final long TYPE_THEME = 4L;

  public static final long TYPE_LOCALE = 8L;

  public static final long TYPE_PLUGIN = 16L;

  public static final long TYPE_MULTI_XPI = 32L;

  public static final long TYPE_ADDON = 30L;

  public static final long TYPE_ANY = 31L;

  public String getId();

  public String getVersion();

  public String getMinAppVersion();

  public String getMaxAppVersion();

  public String getInstallLocationKey();

  public String getName();

  public String getXpiURL();

  public String getXpiHash();

  public String getIconURL();

  public String getUpdateRDF();

  public int getType();

  public void init(String arg1, String arg2, String arg3, String arg4, String arg5, String arg6, String arg7, String arg8, String arg9, String arg10, int arg11);

  public String getObjectSource();

}
