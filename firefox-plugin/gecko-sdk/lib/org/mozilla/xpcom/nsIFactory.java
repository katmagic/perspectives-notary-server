/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIFactory">
 **/

package org.mozilla.xpcom;

public interface nsIFactory extends nsISupports
{
  public static final String NS_IFACTORY_IID =
    "{00000001-0000-0000-c000-000000000046}";

  public nsISupports createInstance(nsISupports arg1, String arg2);

  public void lockFactory(boolean arg1);

}
