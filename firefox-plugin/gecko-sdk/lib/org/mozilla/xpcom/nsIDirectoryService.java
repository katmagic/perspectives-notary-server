/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIDirectoryService">
 **/

package org.mozilla.xpcom;

public interface nsIDirectoryService extends nsISupports
{
  public static final String NS_IDIRECTORYSERVICE_IID =
    "{57a66a60-d43a-11d3-8cc2-00609792278c}";

  public void init();

  public void registerProvider(nsIDirectoryServiceProvider arg1);

  public void unregisterProvider(nsIDirectoryServiceProvider arg1);

}
