/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIScriptableInputS">
 **/

package org.mozilla.xpcom;

public interface nsIScriptableInputStream extends nsISupports
{
  public static final String NS_ISCRIPTABLEINPUTSTREAM_IID =
    "{a2a32f90-9b90-11d3-a189-0050041caf44}";

  public void close();

  public void init(nsIInputStream arg1);

  public long available();

  public String read(long arg1);

}
