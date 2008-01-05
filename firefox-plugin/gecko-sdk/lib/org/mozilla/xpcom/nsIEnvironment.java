/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIEnvironment">
 **/

package org.mozilla.xpcom;

public interface nsIEnvironment extends nsISupports
{
  public static final String NS_IENVIRONMENT_IID =
    "{101d5941-d820-4e85-a266-9a3469940807}";

  public void set(String arg1, String arg2);

  public String get(String arg1);

  public boolean exists(String arg1);

}
