/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsICookie2">
 **/

package org.mozilla.xpcom;

public interface nsICookie2 extends nsICookie
{
  public static final String NS_ICOOKIE2_IID =
    "{d3493503-7854-46ed-8284-8af54a847efb}";

  public String getRawHost();

  public boolean getIsSession();

  public long getExpiry();

}
