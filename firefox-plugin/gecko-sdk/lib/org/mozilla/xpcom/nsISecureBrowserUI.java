/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsISecureBrowserUI">
 **/

package org.mozilla.xpcom;

public interface nsISecureBrowserUI extends nsISupports
{
  public static final String NS_ISECUREBROWSERUI_IID =
    "{081e31e0-a144-11d3-8c7c-00609792278c}";

  public void init(nsIDOMWindow arg1);

  public long getState();

  public String getTooltipText();

}
