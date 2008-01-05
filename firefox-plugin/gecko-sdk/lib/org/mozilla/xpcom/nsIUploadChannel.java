/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIUploadChannel">
 **/

package org.mozilla.xpcom;

public interface nsIUploadChannel extends nsISupports
{
  public static final String NS_IUPLOADCHANNEL_IID =
    "{ddf633d8-e9a4-439d-ad88-de636fd9bb75}";

  public void setUploadStream(nsIInputStream arg1, String arg2, int arg3);

  public nsIInputStream getUploadStream();

}
