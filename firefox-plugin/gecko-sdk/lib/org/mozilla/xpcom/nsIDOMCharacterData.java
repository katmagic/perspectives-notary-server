/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIDOMCharacterData">
 **/

package org.mozilla.xpcom;

public interface nsIDOMCharacterData extends nsIDOMNode
{
  public static final String NS_IDOMCHARACTERDATA_IID =
    "{a6cf9072-15b3-11d2-932e-00805f8add32}";

  public String getData();

  public void setData(String arg1);

  public long getLength();

  public String substringData(long arg1, long arg2);

  public void appendData(String arg1);

  public void insertData(long arg1, String arg2);

  public void deleteData(long arg1, long arg2);

  public void replaceData(long arg1, long arg2, String arg3);

}
