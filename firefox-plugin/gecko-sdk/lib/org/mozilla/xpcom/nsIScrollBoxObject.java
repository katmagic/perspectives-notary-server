/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIScrollBoxObject">
 **/

package org.mozilla.xpcom;

public interface nsIScrollBoxObject extends nsISupports
{
  public static final String NS_ISCROLLBOXOBJECT_IID =
    "{56e2ada8-4631-11d4-ba11-001083023c1e}";

  public void scrollTo(int arg1, int arg2);

  public void scrollBy(int arg1, int arg2);

  public void scrollByLine(int arg1);

  public void scrollByIndex(int arg1);

  public void scrollToLine(int arg1);

  public void scrollToElement(nsIDOMElement arg1);

  public void scrollToIndex(int arg1);

  public void getPosition(int[] arg1, int[] arg2);

  public void getScrolledSize(int[] arg1, int[] arg2);

  public void ensureElementIsVisible(nsIDOMElement arg1);

  public void ensureIndexIsVisible(int arg1);

  public void ensureLineIsVisible(int arg1);

}
