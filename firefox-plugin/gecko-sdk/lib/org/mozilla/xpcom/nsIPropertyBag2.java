/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIPropertyBag2">
 **/

package org.mozilla.xpcom;

public interface nsIPropertyBag2 extends nsIPropertyBag
{
  public static final String NS_IPROPERTYBAG2_IID =
    "{9bb35f13-0096-4a31-833a-acd97001132d}";

  public int getPropertyAsInt32(String arg1);

  public long getPropertyAsUint32(String arg1);

  public long getPropertyAsInt64(String arg1);

  public double getPropertyAsUint64(String arg1);

  public double getPropertyAsDouble(String arg1);

  public String getPropertyAsAString(String arg1);

  public String getPropertyAsACString(String arg1);

  public String getPropertyAsAUTF8String(String arg1);

  public boolean getPropertyAsBool(String arg1);

  public nsISupports getPropertyAsInterface(String arg1, String arg2);

}
