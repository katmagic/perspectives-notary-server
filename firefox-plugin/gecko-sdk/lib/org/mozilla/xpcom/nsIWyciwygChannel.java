/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIWyciwygChannel">
 **/

package org.mozilla.xpcom;

public interface nsIWyciwygChannel extends nsIChannel
{
  public static final String NS_IWYCIWYGCHANNEL_IID =
    "{280da566-6f19-4487-a8ca-70c5ba1602c1}";

  public void writeToCacheEntry(String arg1);

  public void closeCacheEntry(long arg1);

  public void setSecurityInfo(nsISupports arg1);

}
