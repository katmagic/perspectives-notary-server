/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIInputStreamPump">
 **/

package org.mozilla.xpcom;

public interface nsIInputStreamPump extends nsIRequest
{
  public static final String NS_IINPUTSTREAMPUMP_IID =
    "{400f5468-97e7-4d2b-9c65-a82aecc7ae82}";

  public void init(nsIInputStream arg1, long arg2, long arg3, long arg4, long arg5, boolean arg6);

  public void asyncRead(nsIStreamListener arg1, nsISupports arg2);

}
