/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIDOMXULMultiSelec">
 **/

package org.mozilla.xpcom;

public interface nsIDOMXULMultiSelectControlElement extends nsIDOMXULSelectControlElement
{
  public static final String NS_IDOMXULMULTISELECTCONTROLELEMENT_IID =
    "{82c72eca-9886-473e-94cd-9de5694b3f88}";

  public String getSelType();

  public void setSelType(String arg1);

  public nsIDOMXULSelectControlItemElement getCurrentItem();

  public void setCurrentItem(nsIDOMXULSelectControlItemElement arg1);

  public int getCurrentIndex();

  public void setCurrentIndex(int arg1);

  public nsIDOMNodeList getSelectedItems();

  public void addItemToSelection(nsIDOMXULSelectControlItemElement arg1);

  public void removeItemFromSelection(nsIDOMXULSelectControlItemElement arg1);

  public void toggleItemSelection(nsIDOMXULSelectControlItemElement arg1);

  public void selectItem(nsIDOMXULSelectControlItemElement arg1);

  public void selectItemRange(nsIDOMXULSelectControlItemElement arg1, nsIDOMXULSelectControlItemElement arg2);

  public void selectAll();

  public void invertSelection();

  public void clearSelection();

  public int getSelectedCount();

  public nsIDOMXULSelectControlItemElement getSelectedItem(int arg1);

}
