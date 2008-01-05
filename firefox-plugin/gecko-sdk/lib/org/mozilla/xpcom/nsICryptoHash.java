/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsICryptoHash">
 **/

package org.mozilla.xpcom;

public interface nsICryptoHash extends nsISupports
{
  public static final String NS_ICRYPTOHASH_IID =
    "{1e5b7c43-4688-45ce-92e1-77ed931e3bbe}";

  public static final short MD2 = 1;

  public static final short MD5 = 2;

  public static final short SHA1 = 3;

  public static final short SHA256 = 4;

  public static final short SHA384 = 5;

  public static final short SHA512 = 6;

  public void init(long arg1);

  public void initWithString(String arg1);

  public void update(short[] arg1, long arg2);

  public void updateFromStream(nsIInputStream arg1, long arg2);

  public String finish(boolean arg1);

}
