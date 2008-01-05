/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIDocumentLoader">
 **/

package org.mozilla.xpcom;

public interface nsIDocumentLoader extends nsISupports
{
  public static final String NS_IDOCUMENTLOADER_IID =
    "{bbe961ee-59e9-42bb-be50-0331979bb79f}";

  public void stop();

  public nsISupports getContainer();

  public nsILoadGroup getLoadGroup();

  public nsIChannel getDocumentChannel();

}
