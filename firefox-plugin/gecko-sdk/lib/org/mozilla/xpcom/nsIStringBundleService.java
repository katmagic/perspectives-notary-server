/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIStringBundleServ">
 **/

package org.mozilla.xpcom;

public interface nsIStringBundleService extends nsISupports
{
  public static final String NS_ISTRINGBUNDLESERVICE_IID =
    "{d85a17c0-aa7c-11d2-9b8c-00805f8a16d9}";

  public nsIStringBundle createBundle(String arg1);

  public nsIStringBundle createExtensibleBundle(String arg1);

  public String formatStatusMessage(long arg1, String arg2);

  public void flushBundles();

}
