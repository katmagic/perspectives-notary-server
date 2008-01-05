/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIChannel">
 **/

package org.mozilla.xpcom;

public interface nsIChannel extends nsIRequest
{
  public static final String NS_ICHANNEL_IID =
    "{c63a055a-a676-4e71-bf3c-6cfa11082018}";

  public static final long LOAD_DOCUMENT_URI = 65536L;

  public static final long LOAD_RETARGETED_DOCUMENT_URI = 131072L;

  public static final long LOAD_REPLACE = 262144L;

  public static final long LOAD_INITIAL_DOCUMENT_URI = 524288L;

  public static final long LOAD_TARGETED = 1048576L;

  public nsIURI getOriginalURI();

  public void setOriginalURI(nsIURI arg1);

  public nsIURI getURI();

  public nsISupports getOwner();

  public void setOwner(nsISupports arg1);

  public nsIInterfaceRequestor getNotificationCallbacks();

  public void setNotificationCallbacks(nsIInterfaceRequestor arg1);

  public nsISupports getSecurityInfo();

  public String getContentType();

  public void setContentType(String arg1);

  public String getContentCharset();

  public void setContentCharset(String arg1);

  public int getContentLength();

  public void setContentLength(int arg1);

  public nsIInputStream open();

  public void asyncOpen(nsIStreamListener arg1, nsISupports arg2);

}
