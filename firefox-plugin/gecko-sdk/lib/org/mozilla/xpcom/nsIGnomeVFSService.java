/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIGnomeVFSService">
 **/

package org.mozilla.xpcom;

public interface nsIGnomeVFSService extends nsISupports
{
  public static final String NS_IGNOMEVFSSERVICE_IID =
    "{4d6b9f23-8682-41b3-bbff-937a958e6496}";

  public static final int APP_KEY_COMMAND = 0;

  public static final int APP_KEY_NAME = 1;

  public static final int APP_KEY_SUPPORTED_URI_SCHEMES = 2;

  public static final int APP_KEY_EXPECTS_URIS = 3;

  public static final int APP_KEY_CAN_OPEN_MULTIPLE = 4;

  public static final int APP_KEY_REQUIRES_TERMINAL = 5;

  public void setAppStringKey(String arg1, int arg2, String arg3);

  public void setAppBoolKey(String arg1, int arg2, boolean arg3);

  public void addMimeType(String arg1, String arg2);

  public void syncAppRegistry();

  public String getMimeTypeFromExtension(String arg1);

  public nsIGnomeVFSMimeApp getAppForMimeType(String arg1);

  public void setAppForMimeType(String arg1, String arg2);

  public String getDescriptionForMimeType(String arg1);

  public void setIconForMimeType(String arg1, String arg2);

  public void setMimeExtensions(String arg1, String arg2);

  public void showURI(nsIURI arg1);

}
