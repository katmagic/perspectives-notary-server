/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIWritableVariant">
 **/

package org.mozilla.xpcom;

public interface nsIWritableVariant extends nsIVariant
{
  public static final String NS_IWRITABLEVARIANT_IID =
    "{5586a590-8c82-11d5-90f3-0010a4e73d9a}";

  public boolean getWritable();

  public void setWritable(boolean arg1);

  public void setAsInt8(short arg1);

  public void setAsInt16(short arg1);

  public void setAsInt32(int arg1);

  public void setAsInt64(long arg1);

  public void setAsUint8(short arg1);

  public void setAsUint16(int arg1);

  public void setAsUint32(long arg1);

  public void setAsUint64(double arg1);

  public void setAsFloat(float arg1);

  public void setAsDouble(double arg1);

  public void setAsBool(boolean arg1);

  public void setAsChar(char arg1);

  public void setAsWChar(char arg1);

  public void setAsID(String arg1);

  public void setAsAString(String arg1);

  public void setAsDOMString(String arg1);

  public void setAsACString(String arg1);

  public void setAsAUTF8String(String arg1);

  public void setAsString(String arg1);

  public void setAsWString(String arg1);

  public void setAsISupports(nsISupports arg1);

  public void setAsInterface(String arg1, nsISupports arg2);

  public void setAsStringWithSize(long arg1, String arg2);

  public void setAsWStringWithSize(long arg1, String arg2);

  public void setAsVoid();

  public void setAsEmpty();

  public void setAsEmptyArray();

  public void setFromVariant(nsIVariant arg1);

}
