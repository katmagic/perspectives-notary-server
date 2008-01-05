/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIDocumentLoaderFa">
 **/

package org.mozilla.xpcom;

public interface nsIDocumentLoaderFactory extends nsISupports
{
  public static final String NS_IDOCUMENTLOADERFACTORY_IID =
    "{df15f850-5d98-11d4-9f4d-0010a4053fd0}";

  public nsIContentViewer createInstance(String arg1, nsIChannel arg2, nsILoadGroup arg3, String arg4, nsISupports arg5, nsISupports arg6, nsIStreamListener[] arg7);

  public nsIContentViewer createInstanceForDocument(nsISupports arg1, nsISupports arg2, String arg3);

  public nsISupports createBlankDocument(nsILoadGroup arg1);

}
