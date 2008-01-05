/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIDOMWindow">
 **/

package org.mozilla.xpcom;

public interface nsIDOMWindow extends nsISupports
{
  public static final String NS_IDOMWINDOW_IID =
    "{a6cf906b-15b3-11d2-932e-00805f8add32}";

  public nsIDOMDocument getDocument();

  public nsIDOMWindow getParent();

  public nsIDOMWindow getTop();

  public nsIDOMBarProp getScrollbars();

  public String getName();

  public void setName(String arg1);

  public int getScrollX();

  public int getScrollY();

  public void scrollTo(int arg1, int arg2);

  public void scrollBy(int arg1, int arg2);

  public nsISelection getSelection();

  public void scrollByLines(int arg1);

  public void scrollByPages(int arg1);

  public void sizeToContent();

}
