/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIDocumentStateLis">
 **/

package org.mozilla.xpcom;

public interface nsIDocumentStateListener extends nsISupports
{
  public static final String NS_IDOCUMENTSTATELISTENER_IID =
    "{050cdc00-3b8e-11d3-9ce4-a458f454fcbc}";

  public void notifyDocumentCreated();

  public void notifyDocumentWillBeDestroyed();

  public void notifyDocumentStateChanged(boolean arg1);

}
