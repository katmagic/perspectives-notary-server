/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIDOMSVGZoomEvent">
 **/

package org.mozilla.xpcom;

public interface nsIDOMSVGZoomEvent extends nsIDOMUIEvent
{
  public static final String NS_IDOMSVGZOOMEVENT_IID =
    "{339a8c7a-552e-4cbc-8d96-8370a3939358}";

  public nsIDOMSVGRect getZoomRectScreen();

  public float getPreviousScale();

  public nsIDOMSVGPoint getPreviousTranslate();

  public float getNewScale();

  public nsIDOMSVGPoint getNewTranslate();

}
