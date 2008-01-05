/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIHTMLObjectResize">
 **/

package org.mozilla.xpcom;

public interface nsIHTMLObjectResizeListener extends nsISupports
{
  public static final String NS_IHTMLOBJECTRESIZELISTENER_IID =
    "{27b00295-349c-429f-ad0c-87b859e77130}";

  public void onStartResizing(nsIDOMElement arg1);

  public void onEndResizing(nsIDOMElement arg1, int arg2, int arg3, int arg4, int arg5);

}
