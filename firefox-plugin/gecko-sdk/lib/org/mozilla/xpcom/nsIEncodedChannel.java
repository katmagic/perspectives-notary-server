/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIEncodedChannel">
 **/

package org.mozilla.xpcom;

public interface nsIEncodedChannel extends nsISupports
{
  public static final String NS_IENCODEDCHANNEL_IID =
    "{30d7ec3a-f376-4652-9276-3092ec57abb6}";

  public nsIUTF8StringEnumerator getContentEncodings();

  public boolean getApplyConversion();

  public void setApplyConversion(boolean arg1);

}
