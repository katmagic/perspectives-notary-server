/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIDOMXULSelectCont">
 **/

package org.mozilla.xpcom;

public interface nsIDOMXULSelectControlElement extends nsIDOMXULControlElement
{
  public static final String NS_IDOMXULSELECTCONTROLELEMENT_IID =
    "{59fec127-2a0e-445b-84b5-a66dc90245db}";

  public nsIDOMXULSelectControlItemElement getSelectedItem();

  public void setSelectedItem(nsIDOMXULSelectControlItemElement arg1);

  public int getSelectedIndex();

  public void setSelectedIndex(int arg1);

  public String getValue();

  public void setValue(String arg1);

  public nsIDOMXULSelectControlItemElement appendItem(String arg1, String arg2);

  public nsIDOMXULSelectControlItemElement insertItemAt(int arg1, String arg2, String arg3);

  public nsIDOMXULSelectControlItemElement removeItemAt(int arg1);

}
