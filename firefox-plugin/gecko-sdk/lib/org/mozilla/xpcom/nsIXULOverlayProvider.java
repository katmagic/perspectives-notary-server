/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIXULOverlayProvid">
 **/

package org.mozilla.xpcom;

public interface nsIXULOverlayProvider extends nsISupports
{
  public static final String NS_IXULOVERLAYPROVIDER_IID =
    "{1d5b5b94-dc47-4050-93b7-ac092e383cad}";

  public nsISimpleEnumerator getXULOverlays(nsIURI arg1);

  public nsISimpleEnumerator getStyleOverlays(nsIURI arg1);

}
