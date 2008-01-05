/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIMultiPartChannel">
 **/

package org.mozilla.xpcom;

public interface nsIMultiPartChannel extends nsISupports
{
  public static final String NS_IMULTIPARTCHANNEL_IID =
    "{ba78db7b-b88c-4b76-baf9-3c2296a585ae}";

  public nsIChannel getBaseChannel();

  public String getContentDisposition();

  public void setContentDisposition(String arg1);

  public long getPartID();

  public boolean getIsLastPart();

}
