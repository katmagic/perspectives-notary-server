/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIWebBrowserStream">
 **/

package org.mozilla.xpcom;

public interface nsIWebBrowserStream extends nsISupports
{
  public static final String NS_IWEBBROWSERSTREAM_IID =
    "{86d02f0e-219b-4cfc-9c88-bd98d2cce0b8}";

  public void openStream(nsIURI arg1, String arg2);

  public void appendToStream(short[] arg1, long arg2);

  public void closeStream();

}
