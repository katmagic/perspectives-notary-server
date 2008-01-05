/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIWebBrowserFocus">
 **/

package org.mozilla.xpcom;

public interface nsIWebBrowserFocus extends nsISupports
{
  public static final String NS_IWEBBROWSERFOCUS_IID =
    "{9c5d3c58-1dd1-11b2-a1c9-f3699284657a}";

  public void activate();

  public void deactivate();

  public void setFocusAtFirstElement();

  public void setFocusAtLastElement();

  public nsIDOMWindow getFocusedWindow();

  public void setFocusedWindow(nsIDOMWindow arg1);

  public nsIDOMElement getFocusedElement();

  public void setFocusedElement(nsIDOMElement arg1);

}
