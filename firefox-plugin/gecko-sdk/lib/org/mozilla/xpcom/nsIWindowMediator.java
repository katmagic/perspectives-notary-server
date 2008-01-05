/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIWindowMediator">
 **/

package org.mozilla.xpcom;

public interface nsIWindowMediator extends nsISupports
{
  public static final String NS_IWINDOWMEDIATOR_IID =
    "{0659cb81-faad-11d2-8e19-b206620a657c}";

  public static final long zLevelTop = 1L;

  public static final long zLevelBottom = 2L;

  public static final long zLevelBelow = 3L;

  public nsISimpleEnumerator getEnumerator(String arg1);

  public nsISimpleEnumerator getXULWindowEnumerator(String arg1);

  public nsISimpleEnumerator getZOrderDOMWindowEnumerator(String arg1, boolean arg2);

  public nsISimpleEnumerator getZOrderXULWindowEnumerator(String arg1, boolean arg2);

  public nsIDOMWindowInternal getMostRecentWindow(String arg1);

  public void addListener(nsIWindowMediatorListener arg1);

  public void removeListener(nsIWindowMediatorListener arg1);

}
