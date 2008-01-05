/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIFileInputStream">
 **/

package org.mozilla.xpcom;

public interface nsIFileInputStream extends nsIInputStream
{
  public static final String NS_IFILEINPUTSTREAM_IID =
    "{e3d56a20-c7ec-11d3-8cda-0060b0fc14a3}";

  public static final int DELETE_ON_CLOSE = 2;

  public static final int CLOSE_ON_EOF = 4;

  public static final int REOPEN_ON_REWIND = 8;

  public void init(nsIFile arg1, int arg2, int arg3, int arg4);

}
