/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIXPTLoader">
 **/

package org.mozilla.xpcom;

public interface nsIXPTLoader extends nsISupports
{
  public static final String NS_IXPTLOADER_IID =
    "{368a15d9-17a9-4c2b-ac3d-a35b3a22b876}";

  public void enumerateEntries(nsILocalFile arg1, nsIXPTLoaderSink arg2);

  public nsIInputStream loadEntry(nsILocalFile arg1, String arg2);

}
