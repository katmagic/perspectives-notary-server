/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIMenuBoxObject">
 **/

package org.mozilla.xpcom;

public interface nsIMenuBoxObject extends nsISupports
{
  public static final String NS_IMENUBOXOBJECT_IID =
    "{f5099746-5049-4e81-a03e-945d5110fee2}";

  public void openMenu(boolean arg1);

  public nsIDOMElement getActiveChild();

  public void setActiveChild(nsIDOMElement arg1);

  public boolean handleKeyPress(nsIDOMKeyEvent arg1);

}
