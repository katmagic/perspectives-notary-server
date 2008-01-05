/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsICommandParams">
 **/

package org.mozilla.xpcom;

public interface nsICommandParams extends nsISupports
{
  public static final String NS_ICOMMANDPARAMS_IID =
    "{83f892cf-7ed3-490e-967a-62640f3158e1}";

  public static final short eNoType = 0;

  public static final short eBooleanType = 1;

  public static final short eLongType = 2;

  public static final short eDoubleType = 3;

  public static final short eWStringType = 4;

  public static final short eISupportsType = 5;

  public static final short eStringType = 6;

  public short getValueType(String arg1);

  public boolean getBooleanValue(String arg1);

  public int getLongValue(String arg1);

  public double getDoubleValue(String arg1);

  public String getStringValue(String arg1);

  public String getCStringValue(String arg1);

  public nsISupports getISupportsValue(String arg1);

  public void setBooleanValue(String arg1, boolean arg2);

  public void setLongValue(String arg1, int arg2);

  public void setDoubleValue(String arg1, double arg2);

  public void setStringValue(String arg1, String arg2);

  public void setCStringValue(String arg1, String arg2);

  public void setISupportsValue(String arg1, nsISupports arg2);

  public void removeValue(String arg1);

  public boolean hasMoreElements();

  public void first();

  public String getNext();

}
