/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIInputStream">
 **/

package org.mozilla.xpcom;

public interface nsIInputStream extends nsISupports
{
  public static final String NS_IINPUTSTREAM_IID =
    "{fa9c7f6c-61b3-11d4-9877-00c04fa0cf4a}";

  public void close();

  public long available();

  public boolean isNonBlocking();

}
