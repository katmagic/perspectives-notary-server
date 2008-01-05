/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIErrorService">
 **/

package org.mozilla.xpcom;

public interface nsIErrorService extends nsISupports
{
  public static final String NS_IERRORSERVICE_IID =
    "{e72f94b2-5f85-11d4-9877-00c04fa0cf4a}";

  public void registerErrorStringBundle(short arg1, String arg2);

  public void unregisterErrorStringBundle(short arg1);

  public String getErrorStringBundle(short arg1);

  public void registerErrorStringBundleKey(long arg1, String arg2);

  public void unregisterErrorStringBundleKey(long arg1);

  public String getErrorStringBundleKey(long arg1);

}
