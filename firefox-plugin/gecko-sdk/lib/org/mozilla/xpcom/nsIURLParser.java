/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIURLParser">
 **/

package org.mozilla.xpcom;

public interface nsIURLParser extends nsISupports
{
  public static final String NS_IURLPARSER_IID =
    "{7281076d-cf37-464a-815e-698235802604}";

  public void parseURL(String arg1, int arg2, long[] arg3, int[] arg4, long[] arg5, int[] arg6, long[] arg7, int[] arg8);

  public void parseAuthority(String arg1, int arg2, long[] arg3, int[] arg4, long[] arg5, int[] arg6, long[] arg7, int[] arg8, int[] arg9);

  public void parseUserInfo(String arg1, int arg2, long[] arg3, int[] arg4, long[] arg5, int[] arg6);

  public void parseServerInfo(String arg1, int arg2, long[] arg3, int[] arg4, int[] arg5);

  public void parsePath(String arg1, int arg2, long[] arg3, int[] arg4, long[] arg5, int[] arg6, long[] arg7, int[] arg8, long[] arg9, int[] arg10);

  public void parseFilePath(String arg1, int arg2, long[] arg3, int[] arg4, long[] arg5, int[] arg6, long[] arg7, int[] arg8);

  public void parseFileName(String arg1, int arg2, long[] arg3, int[] arg4, long[] arg5, int[] arg6);

}
