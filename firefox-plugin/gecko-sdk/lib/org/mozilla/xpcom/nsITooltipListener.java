/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsITooltipListener">
 **/

package org.mozilla.xpcom;

public interface nsITooltipListener extends nsISupports
{
  public static final String NS_ITOOLTIPLISTENER_IID =
    "{44b78386-1dd2-11b2-9ad2-e4eee2ca1916}";

  public void onShowTooltip(int arg1, int arg2, String arg3);

  public void onHideTooltip();

}
