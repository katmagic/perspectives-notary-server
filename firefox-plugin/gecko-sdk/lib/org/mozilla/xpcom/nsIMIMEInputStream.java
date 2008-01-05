/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIMIMEInputStream">
 **/

package org.mozilla.xpcom;

public interface nsIMIMEInputStream extends nsIInputStream
{
  public static final String NS_IMIMEINPUTSTREAM_IID =
    "{dcbce63c-1dd1-11b2-b94d-91f6d49a3161}";

  public boolean getAddContentLength();

  public void setAddContentLength(boolean arg1);

  public void addHeader(String arg1, String arg2);

  public void setData(nsIInputStream arg1);

}
