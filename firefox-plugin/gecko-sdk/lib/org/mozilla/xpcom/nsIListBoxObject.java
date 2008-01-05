/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIListBoxObject">
 **/

package org.mozilla.xpcom;

public interface nsIListBoxObject extends nsISupports
{
  public static final String NS_ILISTBOXOBJECT_IID =
    "{fde7c970-0b4e-49f4-b1eb-974ae6c96336}";

  public nsIListBoxObject getListboxBody();

  public int getRowCount();

  public int getNumberOfVisibleRows();

  public int getIndexOfFirstVisibleRow();

  public void ensureIndexIsVisible(int arg1);

  public void scrollToIndex(int arg1);

  public void scrollByLines(int arg1);

  public nsIDOMElement getItemAtIndex(int arg1);

  public int getIndexOfItem(nsIDOMElement arg1);

}
