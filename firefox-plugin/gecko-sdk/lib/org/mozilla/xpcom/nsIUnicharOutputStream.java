/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIUnicharOutputStr">
 **/

package org.mozilla.xpcom;

public interface nsIUnicharOutputStream extends nsISupports
{
  public static final String NS_IUNICHAROUTPUTSTREAM_IID =
    "{2d00b1bb-8b21-4a63-bcc6-7213f513ac2e}";

  public boolean write(long arg1, int[] arg2);

  public boolean writeString(String arg1);

  public void flush();

  public void close();

}
