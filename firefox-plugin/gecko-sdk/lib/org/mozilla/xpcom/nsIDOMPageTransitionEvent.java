/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIDOMPageTransitio">
 **/

package org.mozilla.xpcom;

public interface nsIDOMPageTransitionEvent extends nsIDOMEvent
{
  public static final String NS_IDOMPAGETRANSITIONEVENT_IID =
    "{b712418b-376f-4f75-b156-5d9ad99fe51f}";

  public boolean getPersisted();

  public void initPageTransitionEvent(String arg1, boolean arg2, boolean arg3, boolean arg4);

}
