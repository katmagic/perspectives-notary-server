/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIBinaryInputStrea">
 **/

package org.mozilla.xpcom;

public interface nsIBinaryInputStream extends nsIInputStream
{
  public static final String NS_IBINARYINPUTSTREAM_IID =
    "{7b456cb0-8772-11d3-90cf-0040056a906e}";

  public void setInputStream(nsIInputStream arg1);

  public boolean readBoolean();

  public short read8();

  public int read16();

  public long read32();

  public double read64();

  public float readFloat();

  public double readDouble();

  public String readCString();

  public String readString();

  public String readBytes(long arg1);

  public short[] readByteArray(long arg1);

}
