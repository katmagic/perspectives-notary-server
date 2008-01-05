/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIUnicharStreamLoa">
 **/

package org.mozilla.xpcom;

public interface nsIUnicharStreamLoaderObserver extends nsISupports
{
  public static final String NS_IUNICHARSTREAMLOADEROBSERVER_IID =
    "{e06e8b08-8cdd-4503-a0a0-6f3b943602af}";

  public String onDetermineCharset(nsIUnicharStreamLoader arg1, nsISupports arg2, String arg3, long arg4);

  public void onStreamComplete(nsIUnicharStreamLoader arg1, nsISupports arg2, long arg3, nsIUnicharInputStream arg4);

}
