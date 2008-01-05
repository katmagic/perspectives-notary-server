/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIGConfService">
 **/

package org.mozilla.xpcom;

public interface nsIGConfService extends nsISupports
{
  public static final String NS_IGCONFSERVICE_IID =
    "{01ac7b2e-c07c-465f-b35c-542eaef420a9}";

  public boolean getBool(String arg1);

  public String getString(String arg1);

  public int getInt(String arg1);

  public float getFloat(String arg1);

  public void setBool(String arg1, boolean arg2);

  public void setString(String arg1, String arg2);

  public void setInt(String arg1, int arg2);

  public void setFloat(String arg1, float arg2);

  public String getAppForProtocol(String arg1, boolean[] arg2);

  public boolean handlerRequiresTerminal(String arg1);

  public void setAppForProtocol(String arg1, String arg2);

}
