/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIBinaryOutputStre">
 **/

package org.mozilla.xpcom;

public interface nsIBinaryOutputStream extends nsIOutputStream
{
  public static final String NS_IBINARYOUTPUTSTREAM_IID =
    "{204ee610-8765-11d3-90cf-0040056a906e}";

  public void setOutputStream(nsIOutputStream arg1);

  public void writeBoolean(boolean arg1);

  public void write8(short arg1);

  public void write16(int arg1);

  public void write32(long arg1);

  public void write64(double arg1);

  public void writeFloat(float arg1);

  public void writeDouble(double arg1);

  public void writeStringZ(String arg1);

  public void writeWStringZ(String arg1);

  public void writeUtf8Z(String arg1);

  public void writeBytes(String arg1, long arg2);

  public void writeByteArray(short[] arg1, long arg2);

}
