/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIWritableProperty">
 **/

package org.mozilla.xpcom;

public interface nsIWritablePropertyBag2 extends nsIPropertyBag2
{
  public static final String NS_IWRITABLEPROPERTYBAG2_IID =
    "{ee42c54a-19d3-472b-8bc3-76318d5ab5f4}";

  public void setPropertyAsInt32(String arg1, int arg2);

  public void setPropertyAsUint32(String arg1, long arg2);

  public void setPropertyAsInt64(String arg1, long arg2);

  public void setPropertyAsUint64(String arg1, double arg2);

  public void setPropertyAsDouble(String arg1, double arg2);

  public void setPropertyAsAString(String arg1, String arg2);

  public void setPropertyAsACString(String arg1, String arg2);

  public void setPropertyAsAUTF8String(String arg1, String arg2);

  public void setPropertyAsBool(String arg1, boolean arg2);

  public void setPropertyAsInterface(String arg1, nsISupports arg2);

}
